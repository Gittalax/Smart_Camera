#include "common.h"
#include "audio_decode.h"
#include "sdcodec.h"


typedef struct _audio_decode_handle
{
    uint8       channel;
    T_VOID		*pAudioCodec;
    T_AUDIO_DECODE_OUT audio_output;
    pthread_mutex_t     encode_lock;
    char       *out_buf;
}audio_decode_handle, *Paudio_decode_handle;

T_BOOL lnx_delay(T_U32 ticks)
{
    return (usleep (ticks*5000) == 0);
}


/**
* @brief  audio_decode_open
* 		 open a audio decode handle
* @author 	
* @date 	2015/3
* @param:	media_info *pmedia, the medie argments struct
* @return 	void *
* @retval 	ponter to audio decode handle
*/

void * audio_decode_open(media_info *pmedia)
{
    T_AUDIO_DECODE_INPUT audio_input;
    Paudio_decode_handle pdecode_handle = NULL;

	/****  �������ڴ���Դ ****/
    pdecode_handle = (Paudio_decode_handle)malloc(sizeof(audio_decode_handle));
    if(pdecode_handle == NULL)
    {
        anyka_print("[%s:%d] it fails to malloc\n", __func__, __LINE__);
        return pdecode_handle;
    }

	/**** ��ʼ������****/
    memset(&audio_input, 0, sizeof(T_AUDIO_DECODE_INPUT));
    audio_input.cb_fun.Free = (MEDIALIB_CALLBACK_FUN_FREE) free;
    audio_input.cb_fun.Malloc =  (MEDIALIB_CALLBACK_FUN_MALLOC) malloc;
    audio_input.cb_fun.printf = (MEDIALIB_CALLBACK_FUN_PRINTF) anyka_print;
    audio_input.cb_fun.delay = lnx_delay;

    audio_input.m_info.m_Type = pmedia->m_AudioType;
     if (_SD_MEDIA_TYPE_AAC == audio_input.m_info.m_Type)
    {
        //no use setting now
        //may be use in the future.
        anyka_print("aac \n");
        audio_input.m_info.m_Private.m_aac.cmmb_adts_flag = 0;
    }
    audio_input.m_info.m_InbufLen = 20*1024;
    audio_input.m_info.m_SampleRate = pmedia->m_nSamplesPerSec;
    audio_input.m_info.m_Channels = pmedia->m_nChannels;
    audio_input.m_info.m_BitsPerSample = pmedia->m_wBitsPerSample;

//    audio_input.m_info.m_SampleRate = 8000;
 //   audio_input.m_info.m_Channels = 1;
//    audio_input.m_info.m_BitsPerSample = 16;
    
    anyka_print("[%s:%d] Samplerate = %d Channels = %d Bits = %d \n", __func__, __LINE__, 
            pmedia->m_nSamplesPerSec, pmedia->m_nChannels, pmedia->m_wBitsPerSample);
    //must do this
    //audio_input.m_info.m_szData = media_info->m_szData;
    //audio_input.m_info.m_szDataLen = media_info->m_cbSize;


    memset(&pdecode_handle->audio_output, 0, sizeof(T_AUDIO_DECODE_OUT));
    pdecode_handle->channel = pmedia->m_nChannels;
    pthread_mutex_init(&pdecode_handle->encode_lock, NULL); 
    audio_input.chip = AUDIOLIB_CHIP_AK39XXE;

	/** ����Ƶ������ **/
    pdecode_handle->pAudioCodec = _SD_Decode_Open(&audio_input, &pdecode_handle->audio_output);

    if (pdecode_handle->pAudioCodec == AK_NULL)
    {
        free(pdecode_handle);
        anyka_print("[%s:%d] audio decode init failed\n", __func__, __LINE__);
        return NULL;
    }

	/** ���ý������ԣ���ǰ����Ϊ�����ݼ��̽��룬����ȴ���4K������ **/
    _SD_SetBufferMode(pdecode_handle->pAudioCodec, _SD_BM_NORMAL);

    pdecode_handle->out_buf =(char *) malloc(AUDIO_DECODE_MAX_SZ);
	/* �����ڴ�ʧ��ʱ�Ĵ����ͷ���Դ*/
    if(NULL == pdecode_handle->out_buf)		
    {
		_SD_Buffer_Clear(pdecode_handle->pAudioCodec);
		_SD_Decode_Close(pdecode_handle->pAudioCodec);
        free(pdecode_handle);
        anyka_print("[%s:%d] malloc mem err \n", __func__, __LINE__);
        return NULL;
    }
    
    return pdecode_handle;
}

/**
* @brief  audio_decode_get_info
* 		 ��ȡ��Ӧ�������Ϣ
* @author 	
* @date 	2015/3
* @param:	void *handle,	ָ��Ҫ��ȡ���ݵľ�� 
			T_AUDIO_INPUT *out_info	�� ָ������������buf ��ָ��
* @return 	int
* @retval 	0 --> failed, 1--> success
*/

int audio_decode_get_info(void *handle, T_AUDIO_INPUT *out_info)
{
    Paudio_decode_handle pout_info = (Paudio_decode_handle)handle;

	if(pout_info == NULL)
	{
		return 0;
	}
	out_info->nBitsPerSample = pout_info->audio_output.m_BitsPerSample;		//����Ϣ��ֵ�����buf��ֵ
	out_info->nSampleRate = pout_info->audio_output.m_SampleRate;
	out_info->nChannels = pout_info->audio_output.m_Channels;
	return 1;
}


/**
* @brief  audio_decode_get_free
* 		 ��ȡ�����ָ��Ľ��뻺����ʣ��ռ�
* @author 	
* @date 	2015/3
* @param:	void *handle,	ָ��Ҫ��ȡ���ݵľ�� 
* @return 	int
* @retval 	0 --> failed, 1--> success
*/

int audio_decode_get_free(void * handle)
{
    int free_size;
    T_AUDIO_BUF_STATE bufstate;
    T_AUDIO_BUFFER_CONTROL bufctrl;
    Paudio_decode_handle pdecode_handle = (Paudio_decode_handle)handle;

	if(handle == NULL)
    {
        return 0;
    }
	/** lock **/
    pthread_mutex_lock(&pdecode_handle->encode_lock);
    //�ȵõ����뻺�����Ĵ�С
	bufstate  = _SD_Buffer_Check(pdecode_handle->pAudioCodec ,&bufctrl);
	if(_SD_BUFFER_FULL	==	bufstate )		//buf is full
	{
        pthread_mutex_unlock(&pdecode_handle->encode_lock);
		return 0;
	}
	else if(_SD_BUFFER_WRITABLE == bufstate)	// buf is writabal
	{	
		free_size = bufctrl.free_len;
	}
	else
	{	
		free_size = bufctrl.free_len + bufctrl.start_len;
	}	
	/** unlock **/
	pthread_mutex_unlock(&pdecode_handle->encode_lock);
	return free_size;
}


/**
* @brief  audio_decode_add_data
* 		 �������ָ��Ľ��뻺������Ӵ���������
* @author 	
* @date 	2015/3
* @param:	void *handle��	openʱ���صľ�� 
			uint8 * in_buf��ָ���������ݵ�ָ��
			int in_sz�� ��ӵĴ�С
* @return 	int
* @retval 	0 --> failed, 1--> success
*/

int audio_decode_add_data(void * handle, uint8 * in_buf, int in_sz)
{
    
    int free_size;
    T_AUDIO_BUF_STATE bufstate;
    T_AUDIO_BUFFER_CONTROL bufctrl;
    Paudio_decode_handle pdecode_handle = (Paudio_decode_handle)handle;

    if(handle == NULL)
    {
        return 0;
    }
	/** lock **/
    pthread_mutex_lock(&pdecode_handle->encode_lock);
    //�ȵõ����뻺�����Ĵ�С
	bufstate  = _SD_Buffer_Check(pdecode_handle->pAudioCodec ,&bufctrl);
	if(_SD_BUFFER_FULL	==	bufstate )
	{
        pthread_mutex_unlock(&pdecode_handle->encode_lock);
		return 0;
	}
	else if(_SD_BUFFER_WRITABLE == bufstate)
	{	
		free_size = bufctrl.free_len;
	}
	else
	{	
		free_size = bufctrl.free_len + bufctrl.start_len;
	}	
    if(free_size < in_sz)	//���ʣ��ռ䲻�㣬�����ʣ��ռ��С��λ������
    {
        //anyka_print("[audio_decode:audio_decode]: the decode buffer is full,%d,%d\n",free_size ,in_sz);
        in_sz = free_size;
    }

    //����뻺����д������
    if(_SD_BUFFER_WRITABLE == bufstate)
	{		
		memcpy((void *)bufctrl.pwrite, in_buf,  in_sz);		
		_SD_Buffer_Update(pdecode_handle->pAudioCodec, in_sz);
	}
	else
	{
		if(in_sz <= bufctrl.free_len)
		{
			memcpy((void *)bufctrl.pwrite, in_buf, in_sz);
			_SD_Buffer_Update(pdecode_handle->pAudioCodec, in_sz);
		}
		else if(in_sz > bufctrl.free_len)
		{
			int leng = in_sz - bufctrl.free_len;
			memcpy((void *)bufctrl.pwrite, in_buf, bufctrl.free_len);
			_SD_Buffer_Update(pdecode_handle->pAudioCodec, bufctrl.free_len);
			memcpy((void *)bufctrl.pstart, in_buf+bufctrl.free_len, leng);
			_SD_Buffer_Update(pdecode_handle->pAudioCodec, leng);
		}
	}
	/** unlock **/
    pthread_mutex_unlock(&pdecode_handle->encode_lock);
	/** ���سɹ����뻺���������ݴ�С **/
    return in_sz;
    
}


/**
* @brief  audio_decode_set_buf
* 		 ���þ����ָ���ʱ���뻺����С�ӳٳ���.
* @date 	2015/3
* @param:	void *handle��	openʱ���صľ�� 
			int buf_lenf��Ҫ���õĳ���
* @return 	void
* @retval 	
*/

void audio_decode_set_buf(void * handle, int buf_len)
{
	Paudio_decode_handle pdecode_handle = (Paudio_decode_handle)handle;

	/** ���ý����ӿ�ʵ�ֹ��� **/
	_SD_SetInbufMinLen(pdecode_handle->pAudioCodec, buf_len);

	return;
}

/**
* @brief  audio_decode_change_mode
* 		 ���þ���Ľ������ԣ���ǰ����������ȴ�������4K��ֻҪ�����ݾ��ܹ�����
* @date 	2015/3
* @param:	void *handle��	openʱ���صľ�� 
* @return 	void
* @retval 	
*/

void audio_decode_change_mode(void * handle)
{
	Paudio_decode_handle pdecode_handle = (Paudio_decode_handle)handle;
	
	/** ���ý����ӿ�ʵ�ֹ��� **/
	_SD_SetBufferMode(pdecode_handle->pAudioCodec, _SD_BM_LIVE);	

	return;
}

/**
* @brief  audio_decode_decode
* 		���뺯��
* @date 	2015/3
* @param:	void *handle��	openʱ���صľ�� 
			uint8 *out_buf��ָ���Ž�����������ָ��
			uint8 channel������ͨ������1-->��������2-->˫����
* @return 	int
* @retval 	0 --> failed, success-->���سɹ���������ݴ�С
*/

int audio_decode_decode(void *handle, uint8 *out_buf, uint8 channel)
{
	Paudio_decode_handle pdecode_handle = (Paudio_decode_handle)handle;

	T_S32 nSize = 0;

	if(pdecode_handle == NULL)
	{
		return 0;
	}
	pthread_mutex_lock(&pdecode_handle->encode_lock);
	// compute the buffer address and length
	pdecode_handle->audio_output.m_pBuffer = (T_U8 *)pdecode_handle->out_buf;
	pdecode_handle->audio_output.m_ulSize = AUDIO_DECODE_MAX_SZ;
		 
	//decode
	nSize  = _SD_Decode(pdecode_handle->pAudioCodec, &pdecode_handle->audio_output);
     
    if(nSize <= 0)
    {
        pthread_mutex_unlock(&pdecode_handle->encode_lock);
        return nSize;
    }
    
    if(nSize > 0)
    {
        if(pdecode_handle->channel >= channel)
        {
            memcpy(out_buf, pdecode_handle->out_buf, nSize);
        }
        else
        {
            int i;
            uint16 *in , *out;
            in = (uint16 *)pdecode_handle->out_buf;
            out = (uint16 *) out_buf;

            for(i = 0; i < (nSize >> 1); i ++, in++, out++)
            {
                *out = *in ;
				out++;
                *out = *in ;
            }
			nSize = nSize *2;
        }
    }
    pthread_mutex_unlock(&pdecode_handle->encode_lock);
	
    return nSize;
}


/**
* @brief  audio_decode_close
* 		�رս���
* @date 	2015/3
* @param:	void *handle��	openʱ���صľ�� 
* @return 	void
* @retval 	
*/

void audio_decode_close(void *handle)
{
    
    Paudio_decode_handle pdecode_handle = (Paudio_decode_handle)handle;

    if(handle == NULL)
    {
        return ;
    }
    /** �ͷ������Դ **/
    anyka_pthread_mutex_destroy(&pdecode_handle->encode_lock);
	_SD_Buffer_Clear(pdecode_handle->pAudioCodec);
	_SD_Decode_Close(pdecode_handle->pAudioCodec);
    free(pdecode_handle->out_buf);
    free(pdecode_handle);
}



