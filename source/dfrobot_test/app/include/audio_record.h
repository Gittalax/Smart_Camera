#ifndef _AUDIO_RECORD_H_
#define _AUDIO_RECORD_H_
/**
 * NAME         audio_record_start
 * @BRIEF     ��ʼ����¼�����ܣ�Ŀǰ¼��ֻ���� һ���ļ����������ļ����룬
                   
 * @PARAM   audio_path  :¼���ļ���·��
            ext_name    :¼���ļ���׺��(".wav" or ".amr")   
 * @RETURN  void 
 * @RETVAL  
 */

void audio_record_start(char *audio_path, char *ext_name);



/**
 * NAME         audio_record_stop
 * @BRIEF     ֹͣ¼������
                   
 * @PARAM   file_name   ¼���ļ���ȫ·����
 * @RETURN  void 
 * @RETVAL  
 */

void audio_record_stop(char *file_name);

#endif

