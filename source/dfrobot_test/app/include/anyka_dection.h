#ifndef _anyka_dection_h_
#define _anyka_dection_h_
//Ŀǰϵͳֻ�����ƶ���������⹦��
enum
{
    SYS_CHECK_VOICE_ALARM = 1,
    SYS_CHECK_VIDEO_ALARM = 2,
    SYS_CHECK_OTHER_ALARM = 4,
};
typedef void PANYKA_SEND_ALARM_FUNC(int alarm_type, int save_flag, char *save_path, int start_time, int time_len);

/**
 * NAME         anyka_dection_init
 * @BRIEF	ϵͳ����ʱ����ȡ�����ļ������ػ�ǰ�Ƿ�������⣬�������
                    ������Ӧ����,����⵽��Ҫ����Ϣ��ȥ��Ŀǰֻ֧�ִ��ã��������
                    ƽ̨���޸Ļص������Ϳ���
 * @PARAM	Palarm_func  ����������ʱ�Ļص�����
                    filter_check   ��ǰ�Ƿ�������ģ�Ŀǰ�����Ѷ������Ƶ�ۿ���ʱ�������
 * @RETURN	void
 * @RETVAL	
 */


void anyka_dection_init(PANYKA_SEND_ALARM_FUNC Palarm_func, PANYKA_FILTER_VIDEO_CHECK_FUNC filter_check);

/**
 * NAME         anyka_dection_start
 * @BRIEF	����⹦��
 * @PARAM	move_level ���ı�׼
                    check_type �������
                    Palarm_func ���ص�����
                    filter_check   ��ǰ�Ƿ�������ģ�Ŀǰ�����Ѷ������Ƶ�ۿ���ʱ�������
 * @RETURN	void
 * @RETVAL	
 */

void anyka_dection_start(int move_level, int check_type, PANYKA_SEND_ALARM_FUNC Palarm_func, PANYKA_FILTER_VIDEO_CHECK_FUNC filter_check);

/**
 * NAME         anyka_dection_stop
 * @BRIEF	�ر���Ӧ���������,����������ȫ���رգ����ǽ��ͷ�������Դ
 * @PARAM	check_type
 * @RETURN	void
 * @RETVAL	
 */

void anyka_dection_stop(int check_type);

/**
 * NAME         anyka_dection_save_record
 * @BRIEF	���¼���Ƿ�ʼ
 * @PARAM	
 * @RETURN	1-->�������¼��; 0-->���¼��δ��ʼ
 * @RETVAL	
 */

int anyka_dection_save_record(void);


/**
 * NAME         anyka_dection_pause_dection
 * @BRIEF	ֹͣ�ƶ����������
 * @PARAM	
 * @RETURN	
 * @RETVAL	
 */

void anyka_dection_pause_dection(void);

/**
 * NAME         anyka_dection_resume_dection
 * @BRIEF	�ָ��ƶ����������
 * @PARAM	
 * @RETURN	
 * @RETVAL	
 */

void anyka_dection_resume_dection(void);




#endif

