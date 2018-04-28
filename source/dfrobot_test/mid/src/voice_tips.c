
#include "common.h"
#include "sdcodec.h"
#include "audio_decode.h"


/************ define **************/
#define DECODE_SIZE 4096*4
#define CHANNAL 2
#define DA_TYPE ENC_TYPE_PCM
#define MAX_ITEM 30		//�������ֵ
#define PATH_LEN 20

#define FILE_LIST 	"/tmp/alarm_audio_list"	
/*******************************************/

struct voice_tips
{
	int da_flag;//����DA������־λ��������һ�Σ�����
	int run_flag;	//���б�־
	int destroy_flag;	//ֹͣ��־

	void *da_handle;	// da ���
	void *decode_handle; //������
	void *tips_queue;	//��Ƶ�ļ�����
	
	pthread_t msc_pthread;	//�����߳�
	sem_t start;	//�����ź���
};

struct voice_tips voice_tip = {0};


/********************** MUSIC PLAYER *****************************/
/*
*	@param:	PATH �ļ�·��
*	voice_tips ��ͷ�ĺ�����ʾ:anyka_voice_tips
*/
static int voice_tips_openfile(void *file_name)
{
	int voice_tips_fd;

	voice_tips_fd = open(file_name, O_RDONLY);
	if(voice_tips_fd < 0)
	{
		anyka_print("open music file failed, %s\n", strerror(errno));
		return -1;
	}
	
	return voice_tips_fd;
}


/**
* @brief 	voice_tips_decode_init
			��ʼ����ʾ������ģ�鹦��
* @date 	2015/3
* @param:	int enc_type��Ҫ�������ʾ������
* @return 	int
* @retval 	success --> 0; failed --> -1
*/

static int voice_tips_decode_init(int enc_type)
{	
	media_info pmedia;		//decode
	pmedia.m_AudioType = enc_type;
	//pmedia.m_AudioType = _SD_MEDIA_TYPE_MP3;
	pmedia.m_nChannels = 2;
	pmedia.m_nSamplesPerSec = 0;
	pmedia.m_wBitsPerSample = 0;
	
	voice_tip.decode_handle = audio_decode_open(&pmedia);
	if(voice_tip.decode_handle == NULL)
	{
		anyka_print("init decode failed\n");
		return -1;
	}
	
	audio_decode_change_mode(voice_tip.decode_handle);	

	return 0;
}


/**
* @brief 	voice_tips_da_init
			��ʾ��ģ�� DA ��ʼ��
* @date 	2015/3
* @param:	void
* @return 	int
* @retval 	success --> 0; failed --> -1
*/

static int voice_tips_da_init()
{
	T_AUDIO_INPUT param;		//��Ƶ����
	
	/* ��ȡ�����ʵ���Ƶ���� */
	audio_decode_get_info(voice_tip.decode_handle, &param);				
	
	/*anyka_print("[BitsPerSample:%ld] [Channels:%ld] [SampleRate:%ld]\n", param.nBitsPerSample,
		param.nChannels, param.nSampleRate);*/
	
	//open DA
	voice_tip.da_handle = audio_da_open(&param);
	if(voice_tip.da_handle == NULL)
	{
		anyka_print("open DA failed\n");
		return -1;
	}
	
	audio_set_da_vol(voice_tip.da_handle, 2); //С����������ʾ��
	audio_da_clr_buffer(voice_tip.da_handle);

	voice_tip.da_flag = 0;
	
	return 0;
}


/**
* @brief 	voice_tips_play
			������ʾ����ʵ�ʽ�����д��DA
* @date 	2015/3
* @param:	void *handle , open DA ʱ���صľ��
			void *parama, ����������
			int size, ���ݳ���
* @return 	void
* @retval 	
*/

static void voice_tips_play(void *handle , void *parama, int size)
{
	/* write da */	
	audio_write_da(handle, parama, size);
}


/**
* @brief 	voice_tips_decode_data
			��ʾ��ģ�� ���ݽ���
* @date 	2015/3
* @param:	void
* @return 	int
* @retval 	success --> 0; failed --> -1
*/

static int voice_tips_decode_data()
{
	int decode_size = 0, station = 0; 

	char *temp_buf = malloc(DECODE_SIZE * 2);
	if(temp_buf == NULL)
	{
		anyka_print("fail to malloc\n");
		return -1;
	}

	char *decode_outbuf = malloc(DECODE_SIZE * 2);
	if(decode_outbuf == NULL)
	{
		anyka_print("fail to malloc\n");		
		return -1;
	}

	while((decode_size = audio_decode_decode(voice_tip.decode_handle,(uint8*)decode_outbuf, CHANNAL)) > 0)
	{	
		if(voice_tip.da_flag)//��ʼ��1��
		{		
			if(voice_tips_da_init() < 0)
			{
				anyka_print("[%s:%d]Initialize da failed.\n", __func__, __LINE__);
				break;
			}
		}
		
		//store data to temp buffer
		memcpy(temp_buf + station, decode_outbuf, decode_size); 
		station += decode_size;
		
		if(station < DECODE_SIZE)
		{
			continue;
		}
		
		//�����ݽ�DA
		voice_tips_play(voice_tip.da_handle, temp_buf, station);
		break;
	}

	if((decode_size <= 0) && station)
	{
		voice_tips_play(voice_tip.da_handle, temp_buf, station);
	}


	free(temp_buf);
	free(decode_outbuf);
	
	return station;
}



/**
* @brief 	voice_tips_read_data
			��ʾ��ģ�� �����ݣ���ӵ����뻺����������
* @date 	2015/3
* @param:	void
* @return 	void
* @retval 	
*/

static void voice_tips_read_data(int fd)
{
	int free_size, ret, end_flag = 1, encode_size;

	char *decode_buf = malloc(DECODE_SIZE);
	if(decode_buf == NULL)
	{
		anyka_print("[%s:%d]Fail to malloc\n", __func__, __LINE__);
		return;
	}

	voice_tip.da_flag = 1;
	
	while(voice_tip.run_flag)
	{	
		/****  ���free_size��С****/
		free_size = audio_decode_get_free(voice_tip.decode_handle);
		
		/**** free_size ����DECODE_SIZE����ȡDECODE_SIZE ****/
		if((free_size > DECODE_SIZE) && end_flag)
		{	
			free_size = DECODE_SIZE;
			ret = read(fd, decode_buf, free_size);
			if(ret > 0)
			{
				audio_decode_add_data(voice_tip.decode_handle, (uint8 *)decode_buf, ret);
			}
			else
			{
				//anyka_print("[%s:%d]Read to the end of audio file.\n", __func__, __LINE__);
				end_flag = 0;
			}
		}
		encode_size = voice_tips_decode_data();

		if((encode_size == 0) && (end_flag == 0))
		{
			//anyka_print("[%s:%d]Play audio finished.\n", __func__, __LINE__);
			break;
		}	
	}
	
	free(decode_buf);
	
	return;
}



/**
* @brief 	voice_tips_start_play
			��ʾ��ģ�� ��ʼ�����̺߳���
			�ȴ�������ݺ��׳����ź������յ���Ӷ����ж�һ�����ݽ��в���
* @date 	2015/3
* @param:	void
* @return 	int
* @retval 	success --> 0
*/
static int voice_tips_start_play()
{
	char *file_name;
	int fd;

	while(voice_tip.destroy_flag)
	{	
		sem_wait(&voice_tip.start);

		/****** �Ӳ����б�popһ�����ݳ��� ******/
		file_name = (char *)anyka_queue_pop(voice_tip.tips_queue);
		if(file_name == NULL)
		{
			continue;
		}

		/********  open music file  ********/
		if((fd = voice_tips_openfile((void *)file_name)) < 0)
		{
			anyka_print("Can't open file: %s\n", (char *)file_name);	
			free(file_name);
			continue;
		}

		/*** decode init ***/
		voice_tips_decode_init(_SD_MEDIA_TYPE_MP3);
		
		/*** pa enable ***/
        audio_da_spk_enable(1);
		anyka_print("play voice tips: %s\n", (char *)file_name);
		
		/*read and decode, then write DA */
		voice_tips_read_data(fd);

		close(fd);
		free(file_name);
		sleep(3);
		/*** ��ʱ���ȴ����ݲ��ꡣ�ر�DA �� �ر�pa ***/
		audio_decode_close(voice_tip.decode_handle);
       	audio_da_spk_enable(0);
	}
	
	anyka_print("[%s:%d] going to exit\n", __func__, __LINE__);
	return 0;
}


/**
* @brief 	voice_tips_queue_free
			�ͷ���ʾ��������Դ
* @date 	2015/3
* @param:	void *data��ָ��Ҫ�ͷ���Դ��ָ�� 
* @return 	void
* @retval 	
*/

static void voice_tips_queue_free(void *data)
{
	void *tmp = data;

    if(tmp)
    {
        free(tmp);
    }
}

/***********����Ϊģ���ڲ�����**************/

/******************************************************/
/*
*	����Ϊ���⿪�Žӿ�
*/  



/**
* @brief 	voice_tips_init
			��ʾ��ģ���ʼ������
* @date 	2015/3
* @param:	void 
* @return 	int
* @retval 	success --> 0; failed --> -1
*/

/***************  queue init func  ********************/
/**enc_type:��ʼ��ʱ��Ҫ������ļ������ʹ���**/
int voice_tips_init()
{
	if(voice_tip.tips_queue != NULL){
		anyka_print("[%s] It has been initialized.\n", __func__);
		return -1;
	}
	
	memset(&voice_tip, 0, sizeof(voice_tip));
	voice_tip.tips_queue = anyka_queue_init(MAX_ITEM);
	if(voice_tip.tips_queue == NULL)
	{
		anyka_print("init queue failed\n");
		return -1;
	}

	sem_init(&voice_tip.start, 0, 0);
	voice_tip.destroy_flag = 1;
	voice_tip.run_flag = 1;

	/*****************  ������ģ������߳� *****************/
	anyka_pthread_create(&voice_tip.msc_pthread, (void*)voice_tips_start_play,
							NULL, ANYKA_THREAD_MIN_STACK_SIZE, 60);
	
	return 0;
	
}

/**
* @brief 	voice_tips_add_music
			�ⲿͨ�����øýӿ����Ҫ���ŵ��ļ�
* @date 	2015/3
* @param:	void *file_name����Ƶ�ļ��ļ���������·��
* @return 	int
* @retval 	success --> 0; failed --> -1
*/

/************   ����ļ������� ************/
int voice_tips_add_music(void *file_name)
{	
	if(voice_tip.tips_queue == NULL){
		anyka_print("[%s:%d] uninitial\n", __func__, __LINE__);
		return -1;
	}
	
	void *name = malloc(strlen(file_name) + 1);
	if(name == NULL)
	{
		anyka_print("[%s:%d] Fail to malloc\n", __func__, __LINE__);
		return -1;
	}
	strcpy(name, file_name);	//get file name

	
	/*******  ������·��ѹ�����****/
	if(!anyka_queue_push(voice_tip.tips_queue, name))
	{
		anyka_print("Fail to add music\n ");
		return -1;
	}
	sem_post(&voice_tip.start);

	return 0;
}


/**
* @brief 	voice_tips_stop
			��ʾ��ģ��ֹͣ�ӿ�
* @date 	2015/3
* @param:	void 
* @return 	void
* @retval 	
*/

/***   �������ȼ����ʱ����***/
void voice_tips_stop()
{
	void *file_name;
	do
	{
		file_name = anyka_queue_pop(voice_tip.tips_queue);
		if(file_name)
			free(file_name);
	}while(file_name != NULL);
	
	//lock
	// pop all item from queue
	// unlock
	voice_tip.run_flag = 0;
}


/**
* @brief 	voice_tips_destroy
			��ʾ��ģ������ֹͣ�ӿڣ�ͨ���������ͷ���Դ
* @date 	2015/3
* @param:	void 
* @return 	void
* @retval 	
*/

/***********  �ͷ���Դ�ӿ�  ************/
void voice_tips_destroy()
{	
	voice_tips_stop();
	voice_tip.destroy_flag = 0;
	sem_post(&voice_tip.start);
	
	pthread_join(voice_tip.msc_pthread, NULL);
	
	audio_da_close(voice_tip.da_handle);
	audio_decode_close(voice_tip.decode_handle);
	anyka_queue_destroy(voice_tip.tips_queue, voice_tips_queue_free);
	sem_destroy(&voice_tip.start);
	
}

/**
* @brief 	voice_tips_get_file
			��ʾ��ģ���ȡҪ���ŵ��ļ�������Ҫ�Ǻͽű����ʹ��
* @date 	2015/3
* @param:	void 
* @return 	void
* @retval 	
*/

void voice_tips_get_file()
{
	FILE *fp = NULL;
	char audio_name[100] = {0}; 
	/** check file exist **/
	if(access(FILE_LIST, F_OK) != 0)
	{
		anyka_print("[%s:%d] the alarm audio list file isn't exist.\n", __func__, __LINE__);
		return;		
	}
	/*** open file ***/
	fp = fopen(FILE_LIST, "r");
	if(!fp)
	{
		anyka_print("[%s:%d]Open %s failed.\n", __func__, __LINE__, FILE_LIST);
		return;		
	}
	/** read data tu buf  **/
	fread(audio_name, sizeof(char), 99, fp);
	fclose(fp);
	
	audio_name[strlen(audio_name) - 1] = 0;	// delete the end-of-file lable '\n'
	voice_tips_add_music(audio_name);	//add to queue to play

	remove(FILE_LIST);	//remove the file

	return;
}

/****************** File End ********************/
