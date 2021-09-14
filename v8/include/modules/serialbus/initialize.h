#pragma once
#include "framework.h"

#include "serialbus/qmodbusclient_implement.h"
#include "serialbus/qmodbustcpclient_implement.h"
#include "serialbus/qmodbusresponse_implement.h"
#include "serialbus/qmodbusrequest_implement.h"
#include "serialbus/qmodbusreply_implement.h"
#include "serialbus/qmodbuspdu_implement.h"
#include "serialbus/qmodbusdevice_implement.h"
#include "serialbus/qmodbusdataunit_implement.h"


namespace shelllet {
	namespace qtserialbus {
		void initialize(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) {
			using namespace shelllet::core;
			// serialbus
			// https://www.ni.com/zh-cn/innovations/white-papers/14/the-modbus-protocol-in-depth.html
			{
				proto->Set(isolate, ModbusClient::Name(), ModbusClient::WrapClass(isolate));
				proto->Set(isolate, ModbusDataUnit::Name(), ModbusDataUnit::WrapClass(isolate));
				proto->Set(isolate, ModbusDevice::Name(), ModbusDevice::WrapClass(isolate));
				proto->Set(isolate, ModbusPdu::Name(), ModbusPdu::WrapClass(isolate));
				proto->Set(isolate, ModbusReply::Name(), ModbusReply::WrapClass(isolate));
				proto->Set(isolate, ModbusRequest::Name(), ModbusRequest::WrapClass(isolate));
				proto->Set(isolate, ModbusResponse::Name(), ModbusResponse::WrapClass(isolate));
				proto->Set(isolate, ModbusTcpClient::Name(), ModbusTcpClient::WrapClass(isolate));
			}
		}
	
	}
}