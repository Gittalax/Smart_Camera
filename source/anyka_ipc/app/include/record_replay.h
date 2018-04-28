#ifndef _record_replay_h_
#define _record_replay_h_
#include "video_fs_list_manage.h"


typedef void P_RECORD_REPLAY_CALLBACK(T_VOID *param, int type, T_STM_STRUCT *pstream);

/**
 * NAME         record_replay_start
 * @BRIEF	 ����¼��طŹ���
 
 
 * @PARAM    start_time              �طŵĿ�ʼʱ��
                    end_time               �طŵĽ���ʱ��
                    clip_limit   ���Ƶ���ƵƬ��������0��ʾ������, >0 ����Чֵ
                    type                        Ҫ��طŵ����ͣ�֧�־�����¼��ط�
                    mydata                     �û����ݽṹ
                    psend_video_callback ������Ƶ���ݵĻص�����
 * @RETURN	int
 * @RETVAL	1-->fail; 0-->success
 */

int record_replay_start(unsigned long  start_time, unsigned long end_time, int clip_limit,int type, void *mydata, P_RECORD_REPLAY_CALLBACK psend_video_callback);

/**
 * NAME         record_replay_play_status
 * @BRIEF	 ¼��طŵĲ�������ͣ
 
 
 * @PARAM    mydata        �û����ݽṹ�����������طŴ�������
                    play            1-->play; 0-->pause     
 * @RETURN	void
 * @RETVAL	
 */

void record_replay_play_status(void *mydata, int play);

/**
 * NAME         record_replay_stop
 * @BRIEF	 ¼��طŵ�ȡ��
 
 
 * @PARAM    mydata        �û����ݽṹ�����������طŴ�������
 * @RETURN	void
 * @RETVAL	
 */
void record_replay_stop(void *mydata);
/**
 * NAME         record_replay_init
 * @BRIEF	��ʼ��¼��ط������Ϣ������ֻ�����̴߳���Ȼ��ֱ�ӷ���
 
 
 * @PARAM    void
 * @RETURN	void
 * @RETVAL	
 */

void record_replay_init(void);


/**
 * NAME         record_replay_get_read
 * @BRIEF	�õ����ϼ�¼����һ����¼��Ϣ
  
 * @PARAM    record_list       openʱ�� �ľ��
                    find_end       ���ϼ�¼�����ʱ��
                    result              ��¼��Ϣ����
 * @RETURN	���ҽ��
 * @RETVAL	0-->FAIL, 1-->success
 */

int record_replay_get_read(void *record_list, unsigned long find_end, Precord_replay_info result);


/**
 * NAME         record_replay_get_close_file
 * @BRIEF	�رմ��ļ�
  
 * @PARAM    
 * @RETURN	NONE
 * @RETVAL	
 */


void record_replay_get_close_file(void *record_list);

/**
 * NAME         record_replay_get_open_file
 * @BRIEF	��¼���ļ���¼�������õ�ָ��λ��
  
 * @PARAM    type                �طŵ�����
                    start_time       ��Ҫ��¼�Ŀ�ʼʱ��
                    find_end       ���ط��ϼ�¼�����ʱ��
                    result              ��¼��Ϣ����
 * @RETURN	�����ļ����
 * @RETVAL	NULL-->FAIL, other-->success
 */


void * record_replay_get_open_file(int type, unsigned long start_time, unsigned long find_end, Precord_replay_info result);






#endif


