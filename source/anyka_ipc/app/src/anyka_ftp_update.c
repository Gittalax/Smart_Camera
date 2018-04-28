#include "common.h"
#include "anyka_config.h"
#include "anyka_ftp_update.h"

#define UPDATE_DIR      "/tmp/"

#define UPDATE_VERSION  "version.cfg"
#define UPDATE_KERNEL   "zImage"
#define UPDATE_FS       "root.sqsh4"
#define KERNEL_KEY_BEG  "<kv>"
#define KERNEL_KEY_END  "</kv>"
#define FS_KEY_BEG  "<fv>"
#define FS_KEY_END  "</fv>"

#define FS_UPDATE_FLAG 1
#define KERNEL_UPDATE_FLAG 2

/**************** get next 6 info from ini file  ********************/
//#define UPDATE_START_TIME   (2*60*60)
//#define UPDATE_END_TIME   (4*60*60)
//for FTP update
//#define FTP_SERVER "121.14.38.22"
//#define USER_NAME "anyka_ipc"
//#define PASSWORD "Anyka_Ipc"
//#define FTP_FILE_PATH "38Module/IPC-A/"
//#define FTP_FILE_PATH "IntCamPTZ/IntCam-A/"

char* anyka_get_verion(void);

/**
 * NAME         anyka_ftp_update_start_time
 * @BRIEF	��ȡFTP ������ʼʱ��
 * @PARAM	
 * @RETURN	void
 * @RETVAL	
 */

int anyka_ftp_update_start_time()
{
	system_ftp_update_info *ftp_update = anyka_get_sys_ftp_update_info();
	return ftp_update->update_start_time * (60*60);
}


/**
 * NAME         anyka_ftp_update_end_time
 * @BRIEF	��ȡFTP ��������ʱ��
 * @PARAM	
 * @RETURN	void
 * @RETVAL	
 */

int anyka_ftp_update_end_time()
{
	system_ftp_update_info *ftp_update = anyka_get_sys_ftp_update_info();
	return ftp_update->update_end_time * (60*60);
}


/**
 * NAME         anyka_ftp_ftp_server
 * @BRIEF	��ȡFTP ��������ַ
 * @PARAM	
 * @RETURN	void
 * @RETVAL	
 */

char * anyka_ftp_ftp_server()
{
	system_ftp_update_info *ftp_update = anyka_get_sys_ftp_update_info();
	return ftp_update->ftp_server;
}

/**
 * NAME         anyka_ftp_user_name
 * @BRIEF	��ȡ�û���
 * @PARAM	
 * @RETURN	void
 * @RETVAL	
 */

char * anyka_ftp_user_name()
{
	system_ftp_update_info *ftp_update = anyka_get_sys_ftp_update_info();
	return ftp_update->user_name;
}

/**
 * NAME         anyka_ftp_password
 * @BRIEF	��ȡ����
 * @PARAM	
 * @RETURN	void
 * @RETVAL	
 */

char * anyka_ftp_password()
{
	system_ftp_update_info *ftp_update = anyka_get_sys_ftp_update_info();
	return ftp_update->password;
}

/**
 * NAME         anyka_ftp_ftp_file_path
 * @BRIEF	��ȡ�ļ�·��
 * @PARAM	
 * @RETURN	void
 * @RETVAL	
 */

char * anyka_ftp_ftp_file_path()
{
	system_ftp_update_info *ftp_update = anyka_get_sys_ftp_update_info();
	return ftp_update->ftp_file_path;
}

#define UPDATE_START_TIME 	anyka_ftp_update_start_time()
#define UPDATE_END_TIME   	anyka_ftp_update_end_time()
#define FTP_SERVER 			anyka_ftp_ftp_server()
#define USER_NAME 			anyka_ftp_user_name()
#define PASSWORD 			anyka_ftp_password()
#define FTP_FILE_PATH 		anyka_ftp_ftp_file_path()


/**
 * NAME         anyka_get_kernel_version
 * @BRIEF	��ȡ�ں˰汾��
 * @PARAM	
 * @RETURN	void
 * @RETVAL	
 */

int anyka_get_kernel_version(char *version)
{
 
    char buf[200], *src; 
    FILE *filp;
    filp = popen("cat /proc/version", "r");
    if (NULL == filp)
    {
        anyka_print("[%s:%d] popen fail!\n", __func__, __LINE__);
        return -2;
    }
     
    version[0] = 0;
    memset(buf, '\0', sizeof(buf));
    fread(buf, sizeof(char), sizeof(buf)-1, filp);
    src = strstr(buf,"-AKV_");
    if(NULL != src)
    {
        memcpy(version, src + strlen("-AKV_"), 6);
        version[6] = 0;
        anyka_print("system version:%s\n", version);
    }
     
    pclose(filp);
    return strlen(version); 
}


/**
 * NAME         anyka_ftp_find_key_str
 * @BRIEF	���ҹؼ���ʶ��
 * @PARAM	char *src��Դ�ļ�
 			char *dest�� Ŀ���ļ�
 			char *start�� ��ʼ�ַ�
 			char *end�������ַ�
 * @RETURN	int
 * @RETVAL	�ҵ�����0������-1
 */

int anyka_ftp_find_key_str(char *src, char *dest, char *start, char *end)
{
    int len;
    char *find_start, *find_end;
    
    find_start = strstr(src, start);
    find_end = strstr(src, end);
    if(find_start && find_end)
    {
        find_start += strlen(start);
        len = find_end - find_start;
        memcpy(dest, find_start, len);
        dest[len] = 0;
        return 0;
    }
    else
    {
        return -1;
    }
}

/**
* NAME		   anyka_ftp_get_file
* @BRIEF   ͨ��ftp��ȡ����ӳ���ļ�
* @PARAM   char *file_name��Ҫ��ȡ���ļ���
* @RETURN  int
* @RETVAL  ���ػ�ȡ�����ļ��Ĵ�С
*/

int anyka_ftp_check_update(void)
{
    int ret = 0;
    int version_fp;
    char *update_buf, *sys_fs_version, sys_kernel_version[50];
    char kernel_version[50], fs_version[50];
    int file_size;

    strcpy(fs_version, UPDATE_DIR);
    strcat(fs_version, UPDATE_VERSION);
    version_fp = open( UPDATE_VERSION , O_RDONLY);
    if(version_fp < 0)
    {
        anyka_print("[%s:%d] fail to open the update file !\n", __func__, __LINE__);
        return ret;
    }
    
    update_buf = malloc(1024);

    if(NULL == update_buf)
    {
        anyka_print("[%s:%d] fail to malloc !\n", __func__, __LINE__);
        close(version_fp);
        return ret;
    }

    memset(update_buf, 0, 1024);
    file_size = read(version_fp, update_buf, 1024);
    if(file_size == 0)
    {
        anyka_print("[%s:%d] fail to read the version file !\n", __func__, __LINE__);
        free(update_buf);
        close(version_fp);
        return ret;        
    }
    
    close(version_fp);
    if((anyka_ftp_find_key_str(update_buf, kernel_version, KERNEL_KEY_BEG, KERNEL_KEY_END) < 0) ||
        (anyka_ftp_find_key_str(update_buf, fs_version, FS_KEY_BEG, FS_KEY_END) < 0))
    {
        anyka_print("[%s:%d] fail to get version info!\n", __func__, __LINE__);
        free(update_buf);
        return ret;   
    }
    free(update_buf);


    sys_fs_version = anyka_get_verion();

    
    if(strcmp(sys_fs_version, fs_version))
    {
        ret |= FS_UPDATE_FLAG;
    }

    anyka_get_kernel_version(sys_kernel_version);

    if(strcmp(sys_kernel_version, kernel_version))
    {
        ret |= KERNEL_UPDATE_FLAG;
    }

    return ret;

    
}

 /**
 * NAME         anyka_ftp_get_file
 * @BRIEF	ͨ��ftp��ȡ����ӳ���ļ�
 * @PARAM	char *file_name��Ҫ��ȡ���ļ���
 * @RETURN	int
 * @RETVAL	���ػ�ȡ�����ļ��Ĵ�С
 */
int anyka_ftp_get_file(char *file_name)
{
    char cmd[100] = {0}, ftp_file[100]; 
    
	struct stat 	statbuf;
    chdir("/tmp");
    strcpy(ftp_file, FTP_FILE_PATH);
    strcat(ftp_file, file_name);
    /***** ftpget ip filename *****/
    //VERSION Ϊ���ص����ص��ļ���
    //FILE_PASH �ֶ���Ϊ�÷�������������rom_pash���ã�����滻��
    sprintf(cmd, "%s -u %s -p %s %s %s %s", "ftpget", USER_NAME, PASSWORD, FTP_SERVER, file_name, ftp_file);
    system(cmd);

    anyka_print("ftp get :%s\n", cmd);

    
    strcpy(ftp_file, "/tmp/");
    strcat(ftp_file, file_name);
    return  stat( ftp_file, &statbuf );
}


/**
* @brief  ��ϵͳͬ��ʱ��������ǰʱ���������������ڣ�
              ������������Ϣ��飬������ֲ���ԣ�����������
* 
* @param[in]  int cur_year  ϵͳ��ǰ���꣬Ŀǰ��Ϊϵͳʱ���ڴ���2014�꣬
                                       ����Ϊͬ����ʱ�䣬���򲻻�����FTP����
                     int cur_time �Ե���00��00��ʼ�㣬����Ϊ��λ����ǰ��ʱ�䣬
* @return void
* @retval none
*/

void anyka_ftp_update_main(int cur_year, int cur_time)
{
    int ret;
    static int ftp_update_flag = 0;
	
    if((cur_year >= 2014) && (cur_time > UPDATE_START_TIME) && (cur_time < UPDATE_END_TIME))
    {
        if(ftp_update_flag == 0)
        {
            if(anyka_ftp_get_file(UPDATE_VERSION) != -1)
            {
                ftp_update_flag = 1;
                anyka_print("[%s:%d] get the update file\n", __func__, __LINE__);
                ret = anyka_ftp_check_update();
                if(ret & FS_UPDATE_FLAG)
                {
                    anyka_print("[%s:%d] we will get the rootfs file\n", __func__, __LINE__);
                    if(anyka_ftp_get_file(UPDATE_FS)!= -1)
                    {                        
                        anyka_print("[%s:%d] get the rootfs file\n", __func__, __LINE__);
                    }
                    else
                    {
                        ret = ret & (~FS_UPDATE_FLAG);
                    }
                }
                
                if(ret & KERNEL_UPDATE_FLAG)
                {
                    anyka_print("[%s:%d] we will get the kernel file\n", __func__, __LINE__);
                    if(anyka_ftp_get_file(UPDATE_KERNEL)!= -1)
                    {                        
                        anyka_print("[%s:%d] get the kernel file\n", __func__, __LINE__);
                    }
                    else
                    {
                        ret = ret & (~KERNEL_UPDATE_FLAG);
                    }
                }
                if(ret)
                {            
                    system("/usr/sbin/update.sh");            
                }
            }
        }
    }
    else
    {
        ftp_update_flag = 0;
    }
}




