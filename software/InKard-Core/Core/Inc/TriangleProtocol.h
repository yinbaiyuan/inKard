#ifndef TriangleProtocol_h
#define TriangleProtocol_h

#include <inttypes.h>

typedef uint8_t byte;

struct ProtocolCallbackDef
{
  uint8_t pId;
  uint32_t recordTime;
  uint32_t timeout;
};

#define TP_PARSE_CALLBACK void (*parse_callback)(byte, uint8_t *, unsigned int, bool)

#define TP_TRANSMIT_CALLBACK void (*trans_callback)(uint8_t *, unsigned int)

#define DEFAULT_PROTOCO_TIMEOUT 5

#define MAX_PROTOCOL_BUFFER 1280

class TriangleProtocol
{
private:
  TP_PARSE_CALLBACK;

  TP_TRANSMIT_CALLBACK;

  ProtocolCallbackDef *m_protoCallbackVec_array[10];

//  Vector<ProtocolCallbackDef *> m_protoCallbackVec;

  void protocolTimeoutRemove(uint8_t pId);

  void InvertUint16(uint16_t *dBuf, uint16_t *srcBuf);

  uint16_t CRC16_MODBUS(uint8_t *data, uint16_t datalen);

public:
  TriangleProtocol();

  ~TriangleProtocol();

  void callbackRegister(TP_PARSE_CALLBACK, TP_TRANSMIT_CALLBACK);

  void waitProtocolTimeout(uint8_t pId, uint32_t timeout = DEFAULT_PROTOCO_TIMEOUT);

  void protocolLoop();
  /*  
协议标准  
    [0]：固定0为开头 
    [1][2]：含开头、自身、有效负载、校验位总长度
    [3]：协议ID
    [4]：奇光板ID , 255 为广播ID
    [5]-[n]:协议有效负载
    [n+1][n+2]:CRC校验码
*/
  TriangleProtocol &tpBegin(byte pid,byte nid);

  TriangleProtocol &tpByte(byte b);

  TriangleProtocol &tpUint16(uint16_t i);

  TriangleProtocol &tpUint32(uint32_t i);

  TriangleProtocol &tpColor(byte r, byte g, byte b);
	
	TriangleProtocol &tpBuffer(byte *buffer,int length);

//  TriangleProtocol &tpStr(const String &str);

  void tpTransmit(bool checkTimeout = false);

  TriangleProtocol &tpBeginReceive();

  TriangleProtocol &tpPushData(uint8_t d);

  void tpParse();

//  String parseString(uint8_t *payload) const;
  
};

extern TriangleProtocol TPT;

#endif
