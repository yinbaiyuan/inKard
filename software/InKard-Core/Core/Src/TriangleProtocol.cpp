#include "TriangleProtocol.h"

static uint8_t m_ptBuffer[MAX_PROTOCOL_BUFFER];

static uint16_t m_ptLength;

TriangleProtocol::TriangleProtocol()
{
  this->parse_callback = 0;
  this->trans_callback = 0;
}

TriangleProtocol::~TriangleProtocol()
{
}

void TriangleProtocol::callbackRegister(TP_PARSE_CALLBACK, TP_TRANSMIT_CALLBACK)
{
  this->parse_callback = parse_callback;
  this->trans_callback = trans_callback;
}

void TriangleProtocol::InvertUint16(uint16_t *dBuf, uint16_t *srcBuf)
{
  uint16_t tmp[4] = {0};
  for (uint8_t i = 0; i < 16; i++)
  {
    if (srcBuf[0] & (1 << i))
      tmp[0] |= 1 << (15 - i);
  }
  dBuf[0] = tmp[0];
}

uint16_t TriangleProtocol::CRC16_MODBUS(uint8_t *data, uint16_t datalen)
{
  uint16_t wCRCin = 0xFFFF;
  uint16_t wCPoly = 0x8005;
  InvertUint16(&wCPoly, &wCPoly);
  while (datalen--)
  {
    wCRCin ^= *(data++);
    for (uint8_t i = 0; i < 8; i++)
    {
      if (wCRCin & 0x01)
        wCRCin = (wCRCin >> 1) ^ wCPoly;
      else
        wCRCin = wCRCin >> 1;
    }
  }
  uint16_t wCRCinTemp = wCRCin;
  return (wCRCin >> 8 & 0x00FF) | (wCRCinTemp << 8 & 0xFF00);
}

void TriangleProtocol::waitProtocolTimeout(uint8_t pId, uint32_t timeout)
{
//  ProtocolCallbackDef *protocolCallbackDef = new ProtocolCallbackDef();
//  protocolCallbackDef->pId = pId;
//  protocolCallbackDef->recordTime = millis();
//  protocolCallbackDef->timeout = timeout;
//  m_protoCallbackVec.push_back(protocolCallbackDef);
}

void TriangleProtocol::protocolTimeoutRemove(uint8_t pId)
{
//  for (int i = m_protoCallbackVec.size() - 1; i >= 0; i--)
//  {
//    ProtocolCallbackDef *protocolCallbackDef = m_protoCallbackVec[i];
//    if (protocolCallbackDef->pId == pId)
//    {
//      m_protoCallbackVec.remove(i);
//      delete protocolCallbackDef;
//      protocolCallbackDef = NULL;
//    }
//  }
}

void TriangleProtocol::protocolLoop()
{
//  for (int i = m_protoCallbackVec.size() - 1; i >= 0; i--)
//  {
//    ProtocolCallbackDef *protocolCallbackDef = m_protoCallbackVec[i];
//    if (millis() - protocolCallbackDef->recordTime > protocolCallbackDef->timeout)
//    {
//      this->parse_callback(protocolCallbackDef->pId, NULL, 0, true);
//      m_protoCallbackVec.remove(i);
//      delete protocolCallbackDef;
//      protocolCallbackDef = NULL;
//    }
//  }
}

TriangleProtocol &TriangleProtocol::tpBegin(byte pid, byte nid)
{
  m_ptBuffer[0] = 0;
  m_ptBuffer[1] = 0;
  m_ptBuffer[2] = 0;
  m_ptLength = 3;
  m_ptBuffer[m_ptLength++] = pid;
  m_ptBuffer[m_ptLength++] = nid;
  return TPT;
}

TriangleProtocol &TriangleProtocol::tpByte(byte b)
{
  m_ptBuffer[m_ptLength++] = b;
  return TPT;
}

TriangleProtocol &TriangleProtocol::tpUint16(uint16_t i)
{
  m_ptBuffer[m_ptLength++] = (i >> 8) & 0xFF;
  m_ptBuffer[m_ptLength++] = (i >> 0) & 0xFF;
  return TPT;
}

TriangleProtocol &TriangleProtocol::tpUint32(uint32_t i)
{
  m_ptBuffer[m_ptLength++] = (i >> 24) & 0xFF;
  m_ptBuffer[m_ptLength++] = (i >> 16) & 0xFF;
  m_ptBuffer[m_ptLength++] = (i >> 8) & 0xFF;
  m_ptBuffer[m_ptLength++] = (i >> 0) & 0xFF;
  return TPT;
}

TriangleProtocol &TriangleProtocol::tpColor(byte r, byte g, byte b)
{
  m_ptBuffer[m_ptLength++] = r;
  m_ptBuffer[m_ptLength++] = g;
  m_ptBuffer[m_ptLength++] = b;
  return TPT;
}

TriangleProtocol &TriangleProtocol::tpBuffer(byte *buffer,int length)
{
    for(int i = 0;i<length;i++)
    {
        m_ptBuffer[m_ptLength++] = buffer[i];
    }
    return TPT;
}


//TriangleProtocol &TriangleProtocol::tpStr(const String &str)
//{
//  int length = str.length();
//  m_ptBuffer[m_ptLength++] = length;
//  for (int i = 0; i < length; i++)
//  {
//    m_ptBuffer[m_ptLength++] = str[i];
//  }
//  return TPT;
//}

void TriangleProtocol::tpTransmit(bool checkTimeout)
{
  m_ptBuffer[1] = ((m_ptLength + 2) >> 8) & 0xFF;
  m_ptBuffer[2] = ((m_ptLength + 2) >> 0) & 0xFF;

  uint16_t crc = this->CRC16_MODBUS(m_ptBuffer, m_ptLength);
  this->tpUint16(crc);

  this->trans_callback(m_ptBuffer, m_ptLength);
  if (checkTimeout)
  {
    this->waitProtocolTimeout(m_ptBuffer[3]);
  }
	TPT.tpBeginReceive();
}

TriangleProtocol &TriangleProtocol::tpBeginReceive()
{
  m_ptLength = 0;
//  memset(m_ptBuffer, 0, sizeof(uint8_t) * MAX_PROTOCOL_BUFFER);
  return TPT;
}

TriangleProtocol &TriangleProtocol::tpPushData(uint8_t d)
{
  if (m_ptLength == 0 && d != 0) //开头过滤
  {
    return TPT;
  }
  m_ptBuffer[m_ptLength++] = d;
  return TPT;
}

void TriangleProtocol::tpParse()
{
  if (m_ptLength < 3)
    return;
  uint16_t pLength = uint16_t(m_ptBuffer[1] << 8) + uint16_t(m_ptBuffer[2]);
  if (pLength > MAX_PROTOCOL_BUFFER)
  {
    TPT.tpBeginReceive();//协议缓存重置
    return;
  }
  if (pLength < 6)
    return; //无有效载荷，协议至少六位
  if (pLength > m_ptLength)
    return; //未完全接收数据，等待
  if (pLength <= m_ptLength)
  {
    if (this->CRC16_MODBUS(m_ptBuffer, pLength) == 0) //crc校验
    {
      uint8_t pId = m_ptBuffer[3];
      this->protocolTimeoutRemove(pId);
      this->parse_callback(pId, m_ptBuffer + 4, pLength - 4, false);
    } else
    {
//      for (int i = 0; i < pLength; i++)
//      {
//        Serial.println("m_ptBuffer[" + String(i) + "]=" + String(m_ptBuffer[i]));
//      }
//      Serial.println("parse failed");
    }
  }
  TPT.tpBeginReceive();//协议缓存重置
}

//String TriangleProtocol::parseString(uint8_t *payload) const
//{
//  uint8_t stringLength = payload[0];
//  char *buff = (char *)malloc(stringLength + 1);
//  memset(buff, 0, stringLength + 1);
//  for (int i = 0; i < stringLength; i++)
//  {
//    buff[i] = payload[i + 1];
//  }
//  String res = String(buff);
//  delete buff;
//  return res;
//}



TriangleProtocol TPT;
