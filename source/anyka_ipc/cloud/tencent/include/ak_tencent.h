#ifndef _ak_tencent_h_
#define _ak_tencent_h_


/**
 * NAME     qq_start_video
 * @BRIEF	��ʼ������Ƶ����
 * @RETURN	true
 * @RETVAL	
 */
bool qq_start_video();

/**
 * NAME     qq_stop_video
 * @BRIEF	�ر���Ƶ����
 * @RETURN	true
 * @RETVAL	
 */
bool qq_stop_video(void);

/**
 * NAME     qq_reset_video
 * @BRIEF	�Ѿ�������֡�ˣ���һ֡������I֡
 * @PARAM	
 * @RETURN	true
 * @RETVAL	
 */
bool qq_reset_video(void);

/**
 * NAME     qq_set_video
 * @BRIEF	���������������仯�����޸�����
 * @PARAM	bit_rate ����
 * @RETURN	true
 * @RETVAL	
 */
bool qq_set_video(int bit_rate);

/**
 * NAME     qq_start_mic
 * @BRIEF	��������Ѷ������Ƶ����
 * @RETURN	true
 * @RETVAL	
 */
bool qq_start_mic(void);

/**
 * NAME     qq_stop_mic
 * @BRIEF	��������Ѷ������Ƶ����
 * @RETURN	true
 * @RETVAL	
 */
bool qq_stop_mic(void);

/**
 * NAME     qq_start_video_replay 
 * @BRIEF	start qq video replay
 * @PARAM	play_time : begin play time
 * @RETURN	NONE
 * @RETVAL	
 */
void qq_start_video_replay(unsigned int play_time);

/**
 * NAME     ak_qq_get_audio_data
 * @BRIEF	��Ѷ�������豸������Ƶ����
 * @PARAM	pcEncData  ���ݻ�����
            nEncDataLen ���ݳ���
 * @RETURN	NONE
 * @RETVAL	
 */
void ak_qq_get_audio_data(tx_audio_encode_param *pAudioEncodeParam, unsigned char *pcEncData, int nEncDataLen);

/**
 * NAME     ak_qq_init
 * @BRIEF	��������Ѷ�Խӵ������Դ��ʼ��
 * @PARAM	
 * @RETURN	NONE
 * @RETVAL	
 */
void ak_qq_init(void);

/**
 * NAME     ak_qq_control_rotate
 * @BRIEF	������
 * @PARAM	rotate_direction: ���ת���ķ���
                    rotate_degree   : ���ת���ĽǶȣ�Ŀǰ���ǲ�֧�֡�ת��Ĭ�ϽǶ�
 * @RETURN	NONE
 * @RETVAL	
 */
int ak_qq_control_rotate(int rotate_direction, int rotate_degree);

/**
 * NAME     ak_qq_send_msg
 * @BRIEF	����ѶQQ�����豸��Ϣ
 * @PARAM	msg_id: ��Ϣ����
            file_name   : ��Ӧ��Ϣ���ļ�ס��
            title :     ��Ϣ�ı���
            content: ��Ϣ������
            alarm_time: ��Ϣ������ʱ�䡣
 * @RETURN	NONE
 * @RETVAL	
 */
void ak_qq_send_msg(int msg_id, char * file_name, char *title, char *content, int alarm_time );

/**
 * NAME     ak_qq_set_video_para
 * @BRIEF	��ʼ������Ƶ����
 * @PARAM	type    ��Ƶ������
 * @RETURN	NONE
 * @RETVAL	
 */
bool ak_qq_set_video_para(int type);

/**
 * NAME     ak_qq_check_video_filter
 * @BRIEF	����Ƿ���������Ƶ 
 * @PARAM	NONE
 * @RETURN	0:û����Ԥ��״̬��1 :��Ԥ��״̬
 * @RETVAL	
 */
int ak_qq_check_video_filter(void);

/**
* NAME     ak_qq_OnUpdateConfirm
* @BRIEF   on update confirm, when user tick the confirm button then we start update   
* @PARAM   NONE
* @RETURN  NONE
* @RETVAL  
*/
void ak_qq_OnUpdateConfirm();

/**
* NAME     ak_qq_get_global_setting
* @BRIEF   use to get the device name and check whether this machine is first start after update
* @PARAM   dev_name: store the device name buf
*          first_start: store the value; 
*          1=> the device is first start; 0=> the device is not first start after update
* @RETURN  int
* @RETVAL  on success, return 0; else return -1;
*/
int ak_qq_get_global_setting(char *dev_name, unsigned short *first_start);

/**
* NAME     ak_qq_change_firmware_update_status 
* @BRIEF   change the firmware update status
* @PARAM   flags: flags 0 or 1
* @RETURN  NONE
* @RETVAL  
*/
void ak_qq_change_firmware_update_status(int flags);

/**
* NAME     ak_qq_start_video_replay 
* @BRIEF   start video replay
* @PARAM   play_time : begin time 
* @RETURN  NONE
* @RETVAL  
*/
void ak_qq_start_video_replay(unsigned int play_time);

/**
* NAME     ak_qq_stop_video_replay 
* @BRIEF   stop video replay
* @PARAM   NONE
* @RETURN  NONE
* @RETVAL  
*/
void ak_qq_stop_video_replay(void);


/**
 * NAME ak_qq_start_voicelink
 * @BRIEF start voicelink to get wifi config info
 * @RETURN NONE
 */
void ak_qq_start_voicelink();

/**
 * NAME ak_qq_stop_voicelink
 * @BRIEF stop voicelink function
 * @RETURN NONE
 */
void ak_qq_stop_voicelink();

#endif


