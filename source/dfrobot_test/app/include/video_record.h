#ifndef _video_record_h_
#define _video_record_h_

/**
 * NAME         video_record_main_loop
 * @BRIEF	�ƻ�¼���������رգ�ͨ���������ļ�����ʱ��Ϊ����������ֹͣ
 * @PARAM	void
 * @RETURN	void
 * @RETVAL	
 */

void video_record_main_loop(void);

/**
 * NAME         video_record_check_run
 * @BRIEF	����Ƿ�����¼��
 * @PARAM	none 
 * @RETURN	0���ز���¼��1��������¼��
 * @RETVAL	
 */

int video_record_check_run(void);

/**
 * NAME         video_record_start
 * @BRIEF	¼������
 * @PARAM	void
 * @RETURN	-1����ʧ�ܣ�1���سɹ�
 * @RETVAL	
 */

int video_record_start(void);

/**
 * NAME         video_record_stop
 * @BRIEF	¼��ֹͣ�����ͷ����е�¼����ص���Դ
 * @PARAM	void
 * @RETURN	void
 * @RETVAL	
 */

void video_record_stop(void);
/**
 * NAME         video_record_err_stop
 * @BRIEF	���¼�������ʧ�ܣ���ֹͣ¼�����ñ�־���ȴ�¼�����
 * @PARAM	void
 * @RETURN	void
 * @RETVAL	
 */
void video_record_err_stop(void);

/**
 * NAME         video_record_update_use_size
 * @BRIEF	������¼���ʹ���˿ռ��Ҫ�������¼���С
 * @PARAM	int file_size �����ļ���С
 * @RETURN	void*
 * @RETVAL	
 */


void video_record_update_use_size(int file_size);

#endif


