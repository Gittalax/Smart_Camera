#ifndef _audio_talk_h_
#define _audio_talk_h_
typedef void * Pnet_get_talk_data(void * user );

/**
 * NAME         audio_speak_start
 * @BRIEF	�����Խ�����,���������ɽ�AD���ݲɼ����������͸�����
 * @PARAM	mydata    �û�����
                    pget_callback       �õ��������ݵĻص�
                    encode_type     ��������
 * @RETURN	void
 * @RETVAL	
 */

void audio_speak_start(void *mydata, AUDIO_SEND_CALLBACK *pcallback, int encode_type);


/**
 * NAME         audio_speak_stop
 * @BRIEF	ֹͣ�Խ�����,�ر�AD���ݱ���
 * @PARAM	encode_type     ��������
 * @RETURN	void
 * @RETVAL	
 */

void audio_speak_stop(void *mydata, int encode_type);

/**
 * NAME         audio_talk_start
 * @BRIEF	�����Խ����ܣ����������ɽ����������ݣ������룬�͸�DA
 * @PARAM	mydata    �û�����
                    pget_callback       �õ��������ݵĻص�
                    encode_type     ��������
 * @RETURN	0--fail; 1-->ok
 * @RETVAL	
 */

uint8 audio_talk_start(void *mydata, Pnet_get_talk_data pget_callback, int encode_type);


/**
 * NAME         audio_talk_status
 * @BRIEF	�����뻺�����ǲ���Ϊ�յ�״̬
 * @PARAM	
 * @RETURN	0-->Ϊ�գ�1-->��Ϊ�� 
 * @RETVAL	
 */

int audio_talk_status(void);



/**
 * NAME         audio_talk_stop
 * @BRIEF	ֹͣ�Խ�����,�����ٽ�����������
 * @PARAM	
 * @RETURN	void
 * @RETVAL	
 */
void audio_talk_stop(void *mydata);

#endif


