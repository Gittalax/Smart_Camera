/**
 * ���������궨�塣
 */

#include <NkUtils/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#ifndef NK_MACRO_H_
#define NK_MACRO_H_
NK_CPP_EXTERN_BEGIN



/**
 * ����С�˶���������
 */
#define NK_ALIGN_LITTLE_END(__v, __av) \
	((__av) <= 0 ? 0 : (\
			((__v > 0) ?\
					((__v) - ((__v) % (__av)))\
					:\
					 ((__v) - ((__v) % (__av)) - ((0 != ((__v) % (__av))) ? (__av) : 0))\
					)))

/**
 * ���ݴ�˶���������
 */
#define NK_ALIGN_BIG_END(__v, __av) \
		((__av) <= 0 ? 0 : (\
			((__v > 0) ?\
					((__v) - ((__v) % (__av)) + ((0 != ((__v) % (__av))) ? (__av) : 0))\
					:\
					 ((__v) - ((__v) % (__av)))\
					)))


/**
 * 16 λ��С��ת����
 */
#define NK_SWAP16(__v)  ((((NK_UInt16)(__v) & 0xff00) >> 8) | (((NK_UInt16)(__v) & 0x00ff) << 8))
 // �����ʹ�С�˻���

/**
 * 32 λ��С��ת����
 */
#define NK_SWAP32(__v)  ((((NK_UInt32)(__v) & 0xff000000) >> 24) |\
                            (((NK_UInt32)(__v) & 0x00ff0000) >> 8) |\
                            (((NK_UInt32)(__v) & 0x0000ff00) << 8) |\
                            (((NK_UInt32)(__v) & 0x000000ff) << 24))


/// ����ڴ�顣
#define NK_BZERO(__ptr, __size) do { memset(__ptr, 0, __size); } while(0)

/// �ַ����Ƚϡ�
/// �����ַ�����ȫ��ͬ��ʱ�򷵻� True�� ���򷵻� False��
#define NK_STRCMP(__str1, __str2) \
	(((strlen(__str1) == strlen(__str2)) && (0 == strcmp(__str1, __str2))) ? NK_True : NK_False)

/// �����ִ�Сд�ַ���ƥ�䡣
/// �����ִ�Сд������£������ַ�����ͬ��ʱ�򷵻� True�� ���򷵻� False��
#define NK_STRCASECMP(__str1, __str2) \
	(((strlen(__str1) == strlen(__str2)) && (0 == strcasecmp(__str1, __str2))) ? NK_True : NK_False)


/// �ַ���ǰ׺�Ƚϡ�
/// �����ַ���ǰ׺��ͬ��ʱ�򷵻� True�� ���򷵻� False��
#define NK_PREFIX_STRCMP(__str, __pre) \
	(strlen(__str) < strlen(__pre) ? NK_False : (0 == strncmp(__str, __pre, strlen(__pre))))

/// �����ִ�Сд�ַ���ǰ׺�Ƚϡ�
/// �����ִ�Сд������£������ַ���ǰ׺��ͬ��ʱ�򷵻� True�� ���򷵻� False��
#define NK_PREFIX_STRCASECMP(__str, __pre) \
	(strlen(__str) < strlen(__pre) ? NK_False : (0 == strncasecmp(__str, __pre, strlen(__pre))))

/// �ַ�����׺�Ƚϡ�
/// �����ַ�����׺��ͬ��ʱ�򷵻� True�� ���򷵻� False��
#define NK_SUFFIX_STRCMP(__str, __sff) \
	(strlen(__str) < strlen(__sff) ? NK_False : (0 == strcmp(__str + strlen(__str) - strlen(__sff), __sff)))

/// �����ִ�Сд�ַ�����׺�Ƚϡ�
/// �����ִ�Сд������£������ַ�����׺��ͬ��ʱ�򷵻� True�� ���򷵻� False��
#define NK_SUFFIX_STRCASECMP(__str, __sff) \
	(strlen(__str) < strlen(__sff) ? NK_False : (0 == strcasecmp(__str + strlen(__str) - strlen(__sff), __sff)))


/**
 * �ַ������ݡ�\n
 * ȥ���ַ�����ͷ�����λ�������Ŀո�\n
 *
 * @param[in]			text			�����ַ�����
 * @param[in,out]		stack			����ַ�����
 * @param[in]			stack_len		ջ���ڴ泤�ȡ�
 *
 * @return		����ַ�����
 */
static inline NK_PChar
NK_STR_TRIM(NK_PChar text, NK_PChar stack, NK_Size stack_len)
{
	NK_Size text_len = strlen(text);
	NK_PChar end_pos = NK_Nil;
	NK_PChar start_pos = NK_Nil;

	if (!stack || stack_len < text_len) {
		/// ���ػ������
		return NK_Nil;
	}

	/// �����ַ����ǿո����ʼλ�á�
	text_len = strlen(text);
	for (start_pos = text; start_pos < text + text_len + 1; ++start_pos) {
		if (' ' != start_pos[0]) {
			text_len = snprintf(stack, stack_len, "%s", start_pos);
			break;
		}
	}

	/// ������ַ����������ֵ������ո�
	for (end_pos = stack + text_len - 1; end_pos >= stack && ' ' == end_pos[0]; --end_pos) {
		end_pos[0] = '\0';
	}

	/// �����޼�����ַ�����
	return stack;
}

/**
 * �ַ����и����ַ�ת����ȫ��д��
 */
static inline NK_Void
NK_STR_TOUPPER(NK_PChar text)
{
	NK_Size len = strlen(text);
	NK_Int i = 0;
	for (i = 0; i < len; ++i) {
		NK_Char chr = text[i];
		if (chr >= 'a' && chr <= 'z') {
			text[i] = chr - 'a' + 'A';
		}
	}
}

/**
 * �ַ����и����ַ�ת����ȫСд��
 */
static inline NK_Void
NK_STR_TOLOWER(NK_PChar text)
{
	NK_Size len = strlen(text);
	NK_Int i = 0;
	for (i = 0; i < len; ++i) {
		NK_Char chr = text[i];
		if (chr >= 'A' && chr <= 'Z') {
			text[i] = chr - 'A' + 'a';
		}
	}
}

/**
 * ���ϵͳ�Ƿ�ΪС��ģʽ��
 * С��ģʽ���� True�����ģʽ���� False��
 */
static inline NK_Boolean NK_IS_LITTLE_END()
{
	union{
    	   NK_UInt32 dword;
    	   NK_UInt8 bytes[4];
	} un;

	un.dword = 0x12345678;
	return (0x78 == un.bytes[0]);
}

/**
 * 4 �ֽ�����ʵ�ֱ������������ת����
 */
static inline NK_UInt32 NK_HTON32(NK_UInt32 h)
{
	/// ������Ϊ��ˣ��������ֽ���ͬ��ֱ�ӷ���
	/// ������ΪС�ˣ�ת���ɴ���ٷ���
	return NK_IS_LITTLE_END() ? NK_SWAP32(h) : h;
}

/**
 * 2 �ֽ�����ʵ�ֱ������������ת����
 */
static inline NK_UInt16 NK_HTON16(NK_UInt16 h)
{
	/// ������Ϊ��ˣ��������ֽ���ͬ��ֱ�ӷ���
	/// ������ΪС�ˣ�ת���ɴ���ٷ���
	return NK_IS_LITTLE_END() ? NK_SWAP16(h) : h;
}

/**
 * 4 �ֽ�����ʵ�������򵽱������ת����
 */
#define NK_NTOH32(__n) NK_HTON32(__n)

/**
 * 2 �ֽ�����ʵ�������򵽱������ת����
 */
#define NK_NTOH16(__n) NK_HTON16(__n)


/**
 * �ն˴�ӡ���ʮ���������ݡ�
 */
#define NK_HEX_DUMP(__binary, __len) \
	do {\
		NK_Int i, line = 0;\
		NK_PByte byte = (NK_PByte)(__binary);\
		while (byte < (NK_PByte)(__binary) + (__len)) {\
			NK_Char plain[32];\
			strcpy(plain, "................");\
			printf("    %08d    ", line++);\
			for (i = 0; i < 16; ++i) {\
				if (i < (NK_PByte)(__binary) - byte + (__len)) {\
					NK_Byte byt = (NK_Char)(byte[i]);\
					printf(" %02x", (NK_UInt32)(byt));\
					if (byt >= 0x21 && byt <= 0x7f) {\
						plain[i] = (NK_Char)(byt);\
					}\
				} else {\
					printf("   ");\
				}\
			}\
			printf("    | %s | \r\n", plain);\
			byte += 16;\
		}\
	} while(0)

NK_CPP_EXTERN_END
#endif /* NK_MACRO_H_ */
