
/**
 * 
 * QQ��2�������㷨C++��
 * Created on 2005-10-26
 * @author admundliu. modify by billjiang
 * @version 1.0
 *
 **/
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<netinet/in.h>
#include <time.h>

#define TEA_DEF_KEY "bcdfjjlmnprss123"
#define TEA_CRYPOR_CONTENT_MAX_LEN 10240
#define TEA_CRYPOR_BUFF_LEN 8
#define TEA_CRYPOR_KEY_LEN 16

class CTeaCryptor
{
    /**
     * ���ܽ���QQ��Ϣ�Ĺ�����. QQ��Ϣ�ļ����㷨��һ��16�εĵ������̣������Ƿ����ģ�ÿһ�����ܵ�Ԫ��8�ֽڣ����Ҳ��8�ֽڣ���Կ��16�ֽ�
     * ������prePlain��ʾǰһ�����Ŀ飬plain��ʾ��ǰ���Ŀ飬crypt��ʾ��ǰ���Ŀ���ܵõ������Ŀ飬preCrypt��ʾǰһ�����Ŀ�
     * f��ʾ�����㷨��d��ʾ�����㷨 ��ô��plain�õ�crypt�Ĺ�����: m_iCrypt = f(m_szPlain &circ; m_iPreCrypt) &circ;
     * m_szPrePlain ���ԣ���crypt�õ�plain�Ĺ�����Ȼ�� m_szPlain = d(m_iCrypt &circ; m_szPrePlain) &circ;
     * m_iPreCrypt ���⣬�㷨�����������ƣ����������ǰ�����ĺ�ֱ����һ�����ֽ������Ա�֤���ĳ�����8�ֽڵı���
     * �����ֽ�����ԭʼ���ĳ����йأ����ķ�����:
     * 
     * <pre>
     * <code>
     * 
     *      ------- ��Ϣ����㷨 ----------- 
     *      a = (���ĳ��� + 10) mod 8
     *      if(a ������ 0) a = 8 - a;
     *      b = ����� &amp; 0xF8 | a;              ����������ǰ�a��ֵ����������
     *      m_szPlain[0] = b;                     Ȼ���b��Ϊ���ĵĵ�0���ֽڣ�������0���ֽھͱ�����a����Ϣ�������Ϣ�ڽ���ʱ��Ҫ�����ҵ��������ĵ���ʼλ��
     *      m_szPlain[1 �� a+2] = ����� &amp; 0xFF;    �����������������ĵĵ�1����a+2���ֽ�
     *      m_szPlain[a+3 �� a+3+���ĳ���-1] = ����; ��a+3�ֽڿ�ʼ��������������
     *      m_szPlain[a+3+���ĳ���, ���] = 0;       ��������0����䵽�ܳ���Ϊ8������Ϊֹ������Ϊֹ�������ˣ���������õ���Ҫ���ܵ���������
     *      ------- ��Ϣ����㷨 ------------
     *   
     * </code>
     * </pre>
     * 
     * @author �����
     * @author notXX
     */

private:
	
	char m_szPlain[8];	 	// ָ��ǰ�����Ŀ�
	char m_szPrePlain[8];	// ��ָ��ǰ��һ�����Ŀ�
	int m_iCrypt;		// ��ǰ���ܵ�����λ��
	int m_iPreCrypt;	//��һ�μ��ܵ����Ŀ�λ�ã��������8
	int m_iPos;     	 			// ��ǰ����ļ��ܽ��ܿ��λ��
	char m_szKey[TEA_CRYPOR_KEY_LEN+1];	// ��Կ
	char m_szErrMsg[128];
	
	// ���ڼ���ʱ����ʾ��ǰ�Ƿ��ǵ�һ��8�ֽڿ飬��Ϊ�����㷨�Ƿ�����
	// �����ʼ��8���ֽ�û�з������ã�������Ҫ�����������
	bool m_bIsHeader;
	
	// �����ʾ��ǰ���ܿ�ʼ��λ�ã�֮����Ҫ��ôһ��������Ϊ�˱��⵱���ܵ����ʱ
	// �����Ѿ�û�����ݣ���ʱ��ͻ��������������������ж����������ó���
	int m_iContextStart;

public:
	
	CTeaCryptor( char* key )
	{
		m_bIsHeader = true;
		
		memset( m_szPlain, 0, 8 );
		memset( m_szPrePlain, 0, 8 );
		memcpy( m_szKey, key, TEA_CRYPOR_KEY_LEN );
		memset( m_szErrMsg, 0, 128 );
	}
		
        /**
         * ����
         * @param szIn ����
         * @param iOffset ���Ŀ�ʼ��λ��
         * @param iLen ���ĳ���
         * @param m_szKey ��Կ
         * @return ����
         */
        /**
         * ���ֽ������offset��ʼ��len���ֽ�ת����һ��unsigned int�� ��Ϊjava����û��unsigned������unsigned
         * intʹ��long��ʾ�ģ� ���len����8������Ϊlen����8�����lenС��8�����λ��0 <br>
         * (edited by notxx) �ı����㷨, ������΢��һ��. ���ҵĻ����ϲ���10000��, ԭʼ�㷨����18s, ����㷨����12s.
         * 
         * @param szIn
         *                   �ֽ�����.
         * @param iOffset
         *                   �����￪ʼת��.
         * @param iLen
         *                   ת������, ���len����8����Ժ����
         * @return
         */
	unsigned int GetUnsignedInt( const char* szIn, int iOffset, int iLen )
	{
		unsigned int ret = 0;
		int end = 0;
		
		if ( iLen > 8 )
			end = iOffset + 8;
		else
			end = iOffset + iLen;
		
		for ( int i = iOffset; i < end; i++ )
		{
			ret <<= 8;
			ret |= szIn[i] & 0xff;
		}
		
		//ret =  ntohl(ret);

		return ret;
			
	}

	//=================================================================================
	/**
	 * @param szIn		��Ҫ���ܵ�����
	 * @param inLen 		���ĳ���
	 * @param m_szKey	��Կ
	 * @return Message		����
	 */
	bool Encrypt( char* szContent, int iContentLen, char* szEncryptedContent, int& iEncryptedLen )
	{
		if ( !szContent || !szEncryptedContent || iContentLen == 0 )
		{
			snprintf( m_szErrMsg, sizeof( m_szErrMsg ), "params invalid" );
			return false;
		}
	
		int iPadding = 0;
		
		iEncryptedLen = 0;
		m_iPreCrypt = 0;
		m_bIsHeader = true;

		// ����ͷ������ֽ���
		m_iPos = ( iContentLen + 0x0A ) % 8;
		if ( m_iPos != 0 )
		{
			m_iPos = 8 - m_iPos;
		}
		
		// ��������ĳ��Ȳ����������ֵ
		if ( ( iContentLen + m_iPos + 10 ) > TEA_CRYPOR_CONTENT_MAX_LEN )
		{
			snprintf( m_szErrMsg, sizeof( m_szErrMsg ), "content len reach limit" );
			return false;
		}
		
		// ����Ĳ�����pos�浽��plain�ĵ�һ���ֽ�����
		// 0xF8������λ�ǿյģ���������pos����Ϊpos��0��7��ֵ����ʾ�ı���ʼ���ֽ�λ��
		m_szPlain[0] = (char)( ( Rand() & 0xF8) | m_iPos );

		// ��������������������plain[1]��plain[m_iPos]֮�������
		for ( int i = 1; i <= m_iPos; i++ )
		{
			m_szPlain[i] = (char)( Rand() & 0xFF );
		}
		m_iPos ++;
		
		// ��һ��8�ֽڿ鵱Ȼû��prePlain������������һ��ȫ0�ĸ���һ��8�ֽڿ�
		for ( int i = 0; i < 8; i++ )
			m_szPrePlain[i] = 0x0;

		// �������2���ֽڵ������������������������8�ֽھͼ���֮
		iPadding = 1;
		while ( iPadding <= 2 )
		{
			if ( m_iPos < 8 )
			{
				m_szPlain[m_iPos] = (char)( Rand() & 0xFF );
				m_iPos++;
				iPadding ++;
			}
			
			if ( m_iPos == 8 )
			{
				DoEncrypt8Bytes( szEncryptedContent, iEncryptedLen );
			}
		}

		// ===========================================
		// ͷ��������ˣ����￪ʼ��������������
		// Ҳ������8�ֽھͼ��ܣ�һֱ�����Ķ���
		int i = 0;
		while ( iContentLen > 0 )
		{
			if ( m_iPos < 8 )
			{
				m_szPlain[m_iPos] = szContent[i++];
				m_iPos++;
				iContentLen --;
			}

			if ( m_iPos == 8 )
			{
				DoEncrypt8Bytes( szEncryptedContent, iEncryptedLen );
			}
		}
		// ===========================================

		// �������0���Ա�֤��8�ֽڵı���
		iPadding = 1;
		while ( iPadding <= 7 )
		{
			if ( m_iPos < 8 )
			{
				m_szPlain[m_iPos++] = 0x0;
				iPadding++;
			}
			if ( m_iPos == 8 )
				DoEncrypt8Bytes( szEncryptedContent, iEncryptedLen );
		}

		return true;
		
	}


        /**
         * @param szIn		��Ҫ�����ܵ�����
         * @param inLen		���ĳ���
         * @return Message 	�ѽ��ܵ���Ϣ
         */	
        bool Decrypt( const char* szContent, int iContentLen, char* szDecryptedContent, int& iDecryptedLen )
	{
		if ( !szContent || !szDecryptedContent || iContentLen == 0 )
		{
			snprintf( m_szErrMsg, sizeof( m_szErrMsg ), "params invalid" );
			return false;
		}
	
		iDecryptedLen = 0;
		m_iCrypt = 0;
		m_iPreCrypt = 0;
		int iCount = 0;

		// ��ΪQQ��Ϣ����֮��������16�ֽڣ����ҿ϶���8�ı������������������
		if ( ( iContentLen % 8 != 0 ) || ( iContentLen < 16 ) )
		{
			return false;
		}
			
		// �õ���Ϣ��ͷ�����ؼ��ǵõ��������Ŀ�ʼ��λ�ã������Ϣ���ڵ�һ���ֽ����棬�������ý��ܵõ��ĵ�һ���ֽ���7����
		Decipher( szContent, m_szPrePlain );
		
		m_iPos = m_szPrePlain[0] & 0x7;

		// �õ��������ĵĳ���
		iCount = iContentLen - m_iPos - 10;
		if ( iCount < 0 || iCount > TEA_CRYPOR_CONTENT_MAX_LEN )
		{
			return false;
		}

		
		// �������ʱ��preCrypt���ͼ���ʱ��һ��8�ֽڿ�û��prePlainһ��������ʱ
		// ��һ��8�ֽڿ�Ҳû��preCrypt���������ｨһ��ȫ0��
		char szBuff[TEA_CRYPOR_BUFF_LEN] = { 0 };
		const char* pContent = szBuff;
		
		// ����preCrypt��λ�õ���0��ע��Ŀǰ��preCryptλ����ָ��m_szBuff�ģ���Ϊjavaû��ָ�룬���������ں���Ҫ���Ƶ�ǰ����buf������
		m_iPreCrypt = 0;
		
		// ��ǰ������λ�ã�Ϊʲô��8����0�أ�ע��ǰ�������Ѿ�������ͷ����Ϣ�ˣ����ڵ�Ȼ��8��
		m_iCrypt = 8;
		m_iContextStart = 8;
		
		// ��1���ͼ����㷨�Ƕ�Ӧ��
		m_iPos ++;

			
		// ��ʼ����ͷ����������������������8�ֽڣ��������һ��
		// ��Ϊ�ǽ�����һ�飬����������һ����� m = in����һ�鵱Ȼ��preCrypt�ˣ����ǲ�����m��
		// �����������8����˵����ʲô��˵����ͷ8���ֽڵ������ǰ�����������Ϣ�ģ���Ȼ����Ҫ��m������Ū����
		// ���ԣ�����Ȼ������8�Ļ���˵����ͷ8���ֽڵ����ĳ���һ��������Ϣ����֮�⣬�����������õ����
		int iPadding = 1;
		while( iPadding <= 2 )
		{
			if ( m_iPos < 8 )
			{
				m_iPos++;
				iPadding++;
			}
			if ( m_iPos == 8 )
			{
				pContent = szContent;
				if (!DoDecrypt8Bytes( szContent, iContentLen ) )
				{
					return false;
				}
			}
		}

			
		// �����ǽ��ܵ���Ҫ�׶Σ����ʱ��ͷ������䶼�Ѿ������ˣ���ʼ����
		// ע���������һ��whileû����8�������һ��if�����õľ���ԭʼ��m���������m����in��
		while( iCount != 0 )
		{
			if ( m_iPos < 8 )
			{
				szDecryptedContent[iDecryptedLen] = (char)( pContent[m_iPreCrypt + m_iPos] ^ m_szPrePlain[m_iPos] );
				
				iDecryptedLen ++;
				iCount --;
				m_iPos ++;
			}

			if ( m_iPos == 8 )
			{
				pContent = szContent;
				m_iPreCrypt = m_iCrypt - 8;
				if ( !DoDecrypt8Bytes( szContent, iContentLen ) )
				{
					return false;
				}
			}
		}

		// ���Ľ��ܲ��֣�����һ��while�Ѿ������Ķ�������ˣ��������ﻹʣ��ʲô�����ˣ���ʣ��β������䣬Ӧ��ȫ��0
		// ���������м���Ƿ������֮����0��������ǵĻ��ǿ϶������ˣ����Է���null
		for ( iPadding = 1; iPadding < 8; iPadding++ )
		{
			if ( m_iPos < 8 )
			{
				if ( ( pContent[m_iPreCrypt + m_iPos] ^ m_szPrePlain[m_iPos] ) != 0 )
				{
					return false;
				}

				
				m_iPos++;
			}
			if ( m_iPos == 8 ) 
			{
				pContent = szContent;
				m_iPreCrypt = m_iCrypt;
				if ( !DoDecrypt8Bytes( szContent, iContentLen ) )
				{
					return false;
				}

			}
		}

		return true;
		
	}

		
private:
	
	//=================================================================================	
        /**
         * ����8�ֽ� 
         */
	void DoEncrypt8Bytes( char* szEncryptedContent, int& iEncryptedLen )
	{
		// �ⲿ�������������˵�� m_szPlain ^ preCrypt��ע�������ж����ǲ��ǵ�һ��8�ֽڿ飬����ǵĻ����Ǹ�prePlain�͵���preCrypt��
		for ( int i = 0; i < 8; i++ )
		{
			if ( m_bIsHeader )
				m_szPlain[i] ^= m_szPrePlain[i];
			else
				m_szPlain[i] ^= szEncryptedContent[m_iPreCrypt + i];
		}

		char szCrypted[8] = { 0 };
		
		// �����ɵ���������˵�� f(m_szPlain ^ m_iPreCrypt)
		Encipher( m_szPlain, szCrypted );

		memcpy( szEncryptedContent + iEncryptedLen, szCrypted, 8 );

		// ���������ɵ��� f(m_szPlain ^ m_iPreCrypt) ^ prePlain
		for ( int i = 0; i < 8; i++ )
		{
			szEncryptedContent[iEncryptedLen + i] ^= m_szPrePlain[i];
		}

		memcpy( m_szPrePlain, m_szPlain, 8 );
	

		// ����˼��ܣ������ǵ���crypt��preCrypt�ȵȶ�����ʱ����
		m_iPreCrypt = iEncryptedLen;
		iEncryptedLen += 8;      
		m_iPos = 0;
		m_bIsHeader = false;
		
	}

        /**
         * ����8���ֽ�
         * @param szIn		�����ֽ�����
         * @param iOffset		�Ӻδ���ʼ����
         * @param iLen		���ĵĳ���
         * @return true		��ʾ���ܳɹ�
         */
	bool DoDecrypt8Bytes( const char* szIn , int iLen )
	{
		// �����һ�������жϺ��滹��û�����ݣ�û�оͷ��أ�����У���ִ�� m_iCrypt ^ m_szPrePlain
		for ( int i = 0; i < 8; i++ )
		{
			if ( m_iContextStart + i >= iLen )
				return true;
			
			m_szPrePlain[i] ^= szIn[m_iCrypt + i];
		}

		// �ã�����ִ�е��� d(m_iCrypt ^ m_szPrePlain)
		Decipher( m_szPrePlain, m_szPrePlain );
		
		// ������ɣ�wait��û���Ŷ�����һ��û��Ŷ�� 
		// �������һ���ŵ�decrypt����ȥ���ˣ���Ϊ���ܵĲ���Ͼ����ǲ�̫һ����
		// ������Щ������ֵ��
		m_iContextStart += 8;
		m_iCrypt += 8;
		m_iPos = 0;
		
		return true;
	
	}
        

	//=================================================================================
	/**
	* ����һ��8�ֽڿ�
	* @param szIn	�����ֽ�����
	* @return		�����ֽ�����
	*/
	void Encipher( char* szIn, char* szEncrypted )
	{
		// ����������16��
		int iLoop = 0x10;
		
		// �õ����ĺ���Կ�ĸ������� 
		// �ⲿֵ�ÿ����Ƿ���Ҫת���ֽ���
		// ==================================
		unsigned int y = GetUnsignedInt( szIn, 0, 4 );
		unsigned int z = GetUnsignedInt( szIn, 4, 4 );
		unsigned int a = GetUnsignedInt( m_szKey, 0, 4 );
		unsigned int b = GetUnsignedInt( m_szKey, 4, 4 );
		unsigned int c = GetUnsignedInt( m_szKey, 8, 4 );
		unsigned int d = GetUnsignedInt( m_szKey, 12, 4 );
		// ==================================
	
		
		// �����㷨��һЩ���Ʊ�����Ϊʲôdelta��0x9E3779B9�أ�
		// �������TEA�㷨��delta��ʵ���Ǿ���sqr(5)-1 * 2^31
		unsigned int sum = 0;
		unsigned int delta = 0x9E3779B9;
	
		// ��ʼ�����ˣ����߰���ģ���Ҳ��������������DES֮��Ĳ�࣬��������������ȥ
		while ( iLoop-- > 0 )
		{
			sum += delta;
					y += ((z << 4) + a) ^ (z + sum) ^ ((z >> 5) + b);
					z += ((y << 4) + c) ^ (y + sum) ^ ((y >> 5) + d);
		}
	
		szEncrypted[3] = (char) y;
		szEncrypted[2] = (char)( y >> 8 );
		szEncrypted[1] = (char)( y >> 16 );
		szEncrypted[0] = (char)( y >> 24 );
		szEncrypted[7] = (char) z;
		szEncrypted[6] = (char)( z >> 8 );
		szEncrypted[5] = (char)( z >> 16 );
		szEncrypted[4] = (char)( z >> 24 );
	
	}
	
	/**
	* ���ܴ�offset��ʼ��8�ֽ�����
	* @param szIn		�����ֽ�����
	* @return			����
	*/
	void Decipher( const char*szIn, char* szDecrypted )
	{
		// ����������16��
		int iLoop = 0x10;
	
		// �õ����ĺ���Կ�ĸ������� 
		// �ⲿֵ�ÿ����Ƿ���Ҫת���ֽ���
		// ==================================
		unsigned int y = GetUnsignedInt( szIn, 0, 4 );
		unsigned int z = GetUnsignedInt( szIn, 4, 4 );
		unsigned int a = GetUnsignedInt( m_szKey, 0, 4 );
		unsigned int b = GetUnsignedInt( m_szKey, 4, 4 );
		unsigned int c = GetUnsignedInt( m_szKey, 8, 4 );
		unsigned int d = GetUnsignedInt( m_szKey, 12, 4 );
		// ==================================
	
		
		// �㷨��һЩ���Ʊ�����Ϊʲôsum������Ҳ�������أ����sum����Ǻ͵��������й�ϵ��
		// ��Ϊdelta����ô�࣬����sum�������ô��Ļ���������ʱ�����������16�Σ����
		// �õ�ʲô�� Yeah���õ�0�����������Ϊ�˵õ��ͼ���ʱ�෴˳��Ŀ��Ʊ������������ܽ���ѽ
		unsigned int sum = 0xE3779B90;
		unsigned int delta = 0x9E3779B9;
	
		// ������ʼ�ˣ� #_#
		while ( iLoop-- > 0 )
		{
					z -= ((y << 4) + c) ^ (y + sum) ^ ((y >> 5) + d);
					y -= ((z << 4) + a) ^ (z + sum) ^ ((z >> 5) + b);
					sum -= delta;
		}
	
		szDecrypted[3] = (char) y;
		szDecrypted[2] = (char)( y >> 8 );
		szDecrypted[1] = (char)( y >> 16 );
		szDecrypted[0] = (char)( y >> 24 );
		szDecrypted[7] = (char) z;
		szDecrypted[6] = (char)( z >> 8 );
		szDecrypted[5] = (char)( z >> 16 );
		szDecrypted[4] = (char)( z >> 24 );
	
	}
	   

		
        /**
         * ���Ǹ�������Ӳ��������������ͷ���ģ����Ϊ�˵��ԣ�������һ���̶�ֵ
         * ������ӿ���ʹ��ͬ������ÿ�μ��ܳ��������Ķ���һ��
         * 
         * @return	�������
         */
        int Rand()
        {
		//srand(time(NULL)); 
		//return rand();
		return 1000;
        }
    
    
    
};

