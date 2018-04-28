#ifndef _video_fs_list_manage_h_
#define _video_fs_list_manage_h_


typedef struct _record_replay_info *Precord_replay_info;

typedef struct _record_replay_info
{
    unsigned long  recrod_start_time;      //¼���ļ�����ʼʱ��
    unsigned long  record_time;      //¼���ļ�����ʱ��
    unsigned long  play_start;      //¼���ļ��Ŀ�ʼ����λ��
    unsigned long  play_time;      //���¼����Ҫ���ŵ�ʱ��
    char    file_name[100];     //¼���ļ���
    Precord_replay_info next;
}record_replay_info;

/**
 * NAME         video_fs_list_insert_file
 * @BRIEF	���һ�����͵�¼���ļ���һ���ڼƻ�¼��򱨾�¼�����
  
 * @PARAM    type                �طŵ�����
                    file_name        ¼���ļ���
 * @RETURN	NONE
 * @RETVAL	
 */
void video_fs_list_insert_file(char *file_name, int type);

/**
 * NAME         video_fs_list_remove_file
 * @BRIEF	ɾ��һ�����͵�¼���ļ���һ���ڼƻ�¼��򱨾�¼�����
  
 * @PARAM    type                �طŵ�����
                    file_name        ¼���ļ���
 * @RETURN	NONE
 * @RETVAL	
 */
void video_fs_list_remove_file(char *file_name, int type);

/**
 * NAME         video_fs_list_get_record
 * @BRIEF	 ͳ�Ʒ��ϻطŵļ�¼��Ϣ
  
 * @PARAM    start_time        �طŵ���ʼʱ��
                    end_time         �طŵĽ���ʱ��
                    type                �طŵ�����
 * @RETURN	���ط��ϻطŵļ�¼ָ��
 * @RETVAL	
 */

Precord_replay_info video_fs_list_get_record(unsigned long  start_time, unsigned long end_time, int clip_limit , int type);

/**
 * NAME         video_fs_list_init
 * @BRIEF	Ӧ�ó�������ʱ������¼���ļ��б�
  
 * @PARAM    user                
 * @RETURN	NONE
 * @RETVAL	
 */

//void record_replay_test();
void video_fs_list_init(  );


#endif
