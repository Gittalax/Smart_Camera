#ifndef _dana_interface_h_
#define _dana_interface_h_


/**
* @brief 	dana_init
			������ƽ̨��ʼ����ں���
* @date 	2015/3
* @param:	char *danale_path�� �������к��ļ�·��
* @return 	void
* @retval 	
*/

void dana_init(char *danale_path);

/**
* @brief 	anyka_send_net_audio
* 			����������Ƶ�ص�
* @date 	2015/3
* @param:	T_VOID *param������
			T_STM_STRUCT *pstream����Ƶ���ݲ���
* @return 	void
* @retval 	
*/

void anyka_send_net_audio(T_VOID *param, T_STM_STRUCT *pstream);

/**
* @brief 	anyka_set_pzt_control
* 			��̨���ƽӿ�
* @date 	2015/3
* @param:	int code ����������
			int para1������
* @return 	void
* @retval 	
*/

void anyka_send_video_move_alarm(int alarm_type, int save_flag, char *save_path, int start_time, int time_len);

/**
* @brief 	anyka_get_talk_data
* 			��ȡ�������ݻص�
* @date 	2015/3
* @param:	T_VOID *param������
* @return 	void *
* @retval 	
*/

void *anyka_get_talk_data(void *param );

/**
* @brief 	anyka_send_dana_pictrue
* 			����������Ƭ�ص�
* @date 	2015/3
* @param:	T_VOID *param������
			T_STM_STRUCT *pstream����Ƶ���ݲ���
* @return 	void 
* @retval 
*/

void anyka_send_dana_pictrue(void *parm, T_STM_STRUCT *pstream);

/**
* @brief 	anyka_send_net_video
* 			����������Ƶ�ص�
* @date 	2015/3
* @param:	T_VOID *param������
			T_STM_STRUCT *pstream����Ƶ���ݲ���
* @return 	void
* @retval 	
*/

void anyka_send_net_video(T_VOID *param, T_STM_STRUCT *pstream);


/**
* @brief 	anyka_set_pzt_control
* 			��̨���ƽӿ�
* @date 	2015/3
* @param:	int code ����������
			int para1������
* @return 	int
* @retval 	�ɹ�0
*/

int anyka_set_pzt_control( int code , int para1);

/**
* @brief 	anyka_dana_record_play
* 			����¼��ط�
* @date 	2015/3
* @param:	unsigned long start_time�� ��ʼʱ��
			void *mydata�� ����
* @return 	int
* @retval 	
*/

int anyka_dana_record_play(unsigned long start_time, void *mydata);

/**
* @brief 	anyka_dana_record_play
* 			��ͣ¼��ط�
* @date 	2015/3
* @param:	void *mydata�� ����
			int play�����ű�־�� 0  ��ͣ
* @return 	int
* @retval 	
*/
void anyka_dana_record_play_pause(void *mydata, int play);

/**
* @brief 	anyka_dana_record_play
* 			ֹͣ¼��ط�
* @date 	2015/3
* @param:	
			void *mydata�� ����
* @return 	int
* @retval 	
*/
void anyka_dana_record_stop(void *mydata);
#endif

