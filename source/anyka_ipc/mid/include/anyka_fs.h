#ifndef _anyka_fs_h_
#define _anyka_fs_h_


/**
 * NAME         anyka_fs_init
 * @BRIEF	�����첽д�ľ��
 * @PARAM	void
**/                   
    
void anyka_fs_init(void);


/**
 * NAME         anyka_fs_reset
 * @BRIEF	�����첽д�ľ��
 * @PARAM	void
**/                   

void anyka_fs_reset(void);



/**
 * NAME         anyka_fs_flush
 * @BRIEF	�����첽д,������Ӧ���ļ�ID���첽д����ȫ��д��
 * @PARAM	file_id   �ļ�ID
                   
 
 * @RETURN	void 
 * @RETVAL	
 */

void anyka_fs_flush(int file_id);
/**
 * NAME         anyka_fs_read
 * @BRIEF	�����ݣ�Ŀǰû����Ҫ�����첽��ʽ ������ֱ�Ӷ�
 * @PARAM	hFile
                    buf
                    size                   
 
 * @RETURN	void 
 * @RETVAL	
 */

T_S32 anyka_fs_read(T_S32 hFile, T_pVOID buf, T_S32 size);
/**
 * NAME         anyka_fs_write
 * @BRIEF	�첽д���ݣ���������첽д�����ֱ��д
 * @PARAM	hFile
                    buf
                    size                   
 
 * @RETURN	void 
 * @RETVAL	
 */

T_S32 anyka_fs_write(T_S32 hFile, T_pVOID buf, T_S32 size);
/**
 * NAME         anyka_fs_seek
 * @BRIEF	SEEK
 * @PARAM	hFile
                    offset
                    whence                   
 
 * @RETURN	void 
 * @RETVAL	
 */

T_S32 anyka_fs_seek(T_S32 hFile, T_S32 offset, T_S32 whence);
/**
 * NAME         anyka_fs_tell
 * @BRIEF	�õ���ǰ�ļ��Ĵ�С
 * @PARAM	hFile                
 
 * @RETURN	void 
 * @RETVAL	
 */
T_S32 anyka_fs_tell(T_S32 hFile);
/**
 * NAME         anyka_fs_isexist
 * @BRIEF	�ļ��Ƿ����
 * @PARAM	hFile                
 
 * @RETURN	void 
 * @RETVAL	
 */

T_S32 anyka_fs_isexist(T_S32 hFile);
/**
 * NAME         anyka_fs_remove_file
 * @BRIEF	���ļ��Ƴ��첽д������
 * @PARAM	file_id   �ļ�ID
                   
 
 * @RETURN	void 
 * @RETVAL	
 */

void anyka_fs_remove_file(int file_id);

/**
 * NAME         anyka_fs_insert_file
 * @BRIEF	��һ���ļ����뵽�첽д������
 * @PARAM	file_id   �ļ�ID
                   
 
 * @RETURN	void 
 * @RETVAL	
 */

void anyka_fs_insert_file(int file_id);

#endif


