/**
 * ��־��Ϣ���Ƶ���ģ�顣
 */

#include <NkUtils/types.h>

#ifndef NK_LOG_H_
#define NK_LOG_H_
NK_CPP_EXTERN_BEGIN

/**
 * ��־����ȼ���
 */
typedef enum Nk_LogLevel
{
	NK_LOG_ALL = (0),
	NK_LOG_LV_DEBUG,
	NK_LOG_LV_INFO,
	NK_LOG_LV_WARN,
	NK_LOG_LV_ERROR,
	NK_LOG_LV_ALERT,
	NK_LOG_NONE,

} NK_LogLevel;

/**
 * Log ����ģ������
 */
struct Nk_Log
{
	/**
	 * ������־����ȼ���\n
	 * ���õȼ���Ҫ����������ȼ�С�ڵ������õȼ��Ż���б��棬����һ�ɶ�����\n
	 * ��־����·���ɽӿ� @ref setLogPath �������á�\n
	 * �����õȼ�Ϊ @ref NK_LOG_LV_NOTICE����ͨ���ӿ� @ref error �ͽӿ� @ref notice ����־ģ��Żᴦ��\n
	 * ���ӿ� @ref info �ͽӿ� @ref debug ����־ģ����Զ�������\n
	 * �����õ�����£�Ĭ���� @ref NK_LOG_LV_ERROR �ȼ���
	 *
	 */
	NK_Void
	(*setLogLevel)(NK_LogLevel level);

	/**
	 * ��ȡ��־����ȼ���
	 */
	NK_LogLevel
	(*getLogLevel)();

	/**
	 * ������־����̨����ȼ���\n
	 * ֻ����������ȼ�С�ڵ������õȼ��Ż��ڿ���̨�����������ԡ�\n
	 * �����õ�����£�Ĭ���� @ref NK_LOG_LV_INFO �ȼ���
	 *
	 */
	NK_Void
	(*setTerminalLevel)(NK_LogLevel level);

	/**
	 * ��ȡ��־����̨����ȼ���
	 */
	NK_LogLevel
	(*getTerminalLevel)();

	/**
	 * ������־��¼��
	 */
	NK_Void
	(*alert)(const NK_PChar fmt, ...);

	/**
	 * ������־��¼��
	 */
	NK_Void
	(*error)(const NK_PChar fmt, ...);

	/**
	 * ֪ͨ��־��¼��
	 */
	NK_Void
	(*warn)(const NK_PChar fmt, ...);

	/**
	 * ��Ϣ��־��¼��
	 */
	NK_Void
	(*info)(const NK_PChar fmt, ...);

	/**
	 * ������Ϣ��¼��
	 */
	NK_Void
	(*debug)(const NK_PChar fmt, ...);

	/**
	 * ģ���ڻᱣ��һ����־���壬���еȼ�С�� Terminal Level ����־���ᱻ��¼���������ڣ�\n
	 * ��������ʱ���Զ������˽ӿڲ�����ͬʱ�ᴥ�� @ref onFlush �¼���\n
	 * �û����Ը��ݾ���ʵ�ַ��������� @ref onFlush �¼��д��������־���ݡ�
	 */
	NK_Void
	(*flush)();

	/**
	 * ��־��������ˢ�¼���\n
	 * �ο� @ref flush��\n
	 * ��Ҫע����ǣ��¼�ʵ���в��ܵ��� NK_Log ģ����ؽӿڣ������ɿ������ڳ�����ѭ����ɵı�����
	 */
	NK_Void
	(*onFlush)(NK_PByte bytes, NK_Size len);

};

/**
 * ��ȡ��������
 */
extern struct Nk_Log
*NK_Log();


/**
 * �ն�����������
 * ��ű����������е������ġ�
 */
typedef struct Nk_TermTable
{
	NK_Byte reserved[128];

} NK_TermTable;

/**
 * ��ʼ�����ն˱��
 * ��ʼ�� @ref Tbl �����
 */
extern NK_Int
NK_TermTbl_BeginDraw(NK_TermTable *Tbl, NK_PChar title, NK_Size width, NK_Size padding);

/**
 * �ն˱��׷��һ�������ı���
 *
 * @param[in]			end_ln			�н�����ʶ��Ϊ True ʱ����׷�Ӻ����ϵײ��߿�
 * @param[in]			fmt				�ı������ʽ��
 *
 * @retval 0		����ɹ���
 * @retval -1		���ʧ�ܡ�
 *
 */
extern NK_Int
NK_TermTbl_PutText(NK_TermTable *Tbl, NK_Boolean end_ln, NK_PChar fmt, ...);

/**
 * �ն˱��׷��һ�С���-ֵ����ʽ���ı�����
 *
 * @param[in]			end_ln			�н�����ʶ��Ϊ True ʱ����׷�Ӻ����ϵײ��߿�
 * @param[in]			key				���ı���
 * @param[in]			fmt				ֵ�ı������ʽ��
 *
 * @retval 0		����ɹ���
 * @retval -1		���ʧ�ܡ�
 *
 */
extern NK_Int
NK_TermTbl_PutKeyValue(NK_TermTable *Tbl, NK_Boolean end_ln, NK_PChar key, NK_PChar fmt, ...);

/**
 * �������ơ�\n
 * ���ô˽ӿڻ����֮ǰ��������׷��һ���ײ��߿򣬲���λ�����
 *
 */
extern NK_Int
NK_TermTbl_EndDraw(NK_TermTable *Tbl);



NK_CPP_EXTERN_END
#endif /* NK_LOG_H_ */
