#ifndef _VOICE_TIPS_H_
#define _VOICE_TIPS_H_

/*
* @PATH:�������·��
* @enc_type:���������������	
*/

/**
* @brief	voice_tips_add_music
			�ⲿͨ�����øýӿ����Ҫ���ŵ��ļ�
* @date 	2015/3
* @param:	void *file_name����Ƶ�ļ��ļ���������·��
* @return	int
* @retval	success --> 0; failed --> -1
*/
int voice_tips_add_music(void *file_name);

/**
* @brief 	voice_tips_init
			��ʾ��ģ���ʼ������
* @date 	2015/3
* @param:	void 
* @return 	int
* @retval 	success --> 0; failed --> -1
*/

int voice_tips_init();

/**
* @brief 	voice_tips_stop
			��ʾ��ģ��ֹͣ�ӿ�
* @date 	2015/3
* @param:	void 
* @return 	void
* @retval 	
*/

void voice_tips_stop();

/**
* @brief 	voice_tips_destroy
			��ʾ��ģ������ֹͣ�ӿڣ�ͨ���������ͷ���Դ
* @date 	2015/3
* @param:	void 
* @return 	void
* @retval 	
*/
void voice_tips_destroy();


/**
* @brief 	voice_tips_get_file
			��ʾ��ģ���ȡҪ���ŵ��ļ�������Ҫ�Ǻͽű����ʹ��
* @date 	2015/3
* @param:	void 
* @return 	void
* @retval 	
*/
void voice_tips_get_file();

#endif


