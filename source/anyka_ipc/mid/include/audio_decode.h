#ifndef _audio_decode_h_
#define _audio_decode_h_

#define 	AUDIO_DECODE_MAX_SZ 2048

typedef struct media_info
{
	int m_AudioType;
	int m_nSamplesPerSec;
	int m_nChannels;
	int m_wBitsPerSample;
}media_info;

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

int audio_decode_get_info(void *handle, T_AUDIO_INPUT *out_info);

/**
* @brief  audio_decode_get_free
* 		 ��ȡ�����ָ��Ľ��뻺����ʣ��ռ�
* @author 	
* @date 	2015/3
* @param:	void *handle,	ָ��Ҫ��ȡ���ݵľ�� 
* @return 	int
* @retval 	0 --> failed, 1--> success
*/

int audio_decode_get_free(void * handle);


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

void * audio_decode_open(media_info *pmedia);

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

int audio_decode_add_data(void *handle, uint8 *in_buf, int in_sz);

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

int audio_decode_decode(void *handle, uint8 *out_buf, uint8 channel);

/**
* @brief  audio_decode_close
* 		�رս���
* @date 	2015/3
* @param:	void *handle��	openʱ���صľ�� 
* @return 	void
* @retval 	
*/

void audio_decode_close(void *handle);

/**
* @brief  audio_decode_change_mode
* 		 ���þ���Ľ������ԣ���ǰ����������ȴ�������4K��ֻҪ�����ݾ��ܹ�����
* @date 	2015/3
* @param:	void *handle��	openʱ���صľ�� 
* @return 	void
* @retval 	
*/

void audio_decode_change_mode(void * handle);


/**
* @brief  audio_decode_set_buf
* 		 ���þ����ָ���ʱ���뻺����С�ӳٳ���.
* @date 	2015/3
* @param:	void *handle��	openʱ���صľ�� 
			int buf_lenf��Ҫ���õĳ���
* @return 	void
* @retval 	
*/

void audio_decode_set_buf(void * handle, int buf_len);



#endif
