/**
 * N1 ö�����ݶ��塣
 *
 */

#include <NkUtils/types.h>

#ifndef NK_ENUM_H_
#define NK_ENUM_H_
NK_CPP_EXTERN_BEGIN

/**
 * δ����ö�ٱ�����
 */
#define NK_ENUM_UNDEFINED ""

/**
 * ����ö��ֵӳ���ı����Ľӿ�ģ�塣
 * ͨ���˽ӿڶ��庯����Ч����ظ������������⡣
 * �궨���ڱ����ʱ���չ������ص����ͽӿڡ�
 */
#define DECLARE_NK_ENUM_MAP(__type)  NK_PChar NK_Enum_Map##__type(NK_##__type enm)

/**
 * �����ı����Ľӿ�ӳ��ö��ֵģ�塣
 */
#define DECLARE_NK_ENUM_UNMAP(__type)  NK_##__type NK_Enum_Unmap##__type(NK_PChar text)


/**
 * ���ö�Ӧ���͵�ö�ٽӿڡ�
 */
#define NK_ENUM_MAP(__type, __enm) NK_Enum_Map##__type(__enm)

/**
 * ���ö�Ӧ���͵�ö�ٽӿڡ�
 */
#define NK_ENUM_UNMAP(__type, __text) NK_Enum_Unmap##__type(__text)



NK_CPP_EXTERN_END
#endif /* NK_N1_ENUM_H_ */
