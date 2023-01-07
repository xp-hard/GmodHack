#include "netvars.h"
#include "interfaces.h"

void SetupNetvars() {
	for (auto node = interfaces::client->GetAllClasses(); node; node = node->m_pNext) {
		if (node->m_pRecvTable) {
			Dump(node->m_pNetworkName, node->m_pRecvTable, 0);
		}
	}
}

void Dump(const char* baseClass, RecvTable* table, intptr_t offset) {
	for (int i = 0; i < table->m_nProps; ++i) {
		const auto prop = &table->m_pProps[i];

		if (!prop || !prop->m_pVarName || isdigit(prop->m_pVarName[0])) {
			continue;
		}

		if (prop->m_pVarName == "baseclass") {
			continue;
		}

		if (
			prop->m_RecvType == SendPropType::DATATABLE &&
			prop->m_pDataTable &&
			prop->m_pDataTable->m_pNetTableName[0] == 'D'
			) {

			Dump(baseClass, prop->m_pDataTable, offset + prop->m_Offset);
		}

		const auto netvarName = std::format("{}->{}", baseClass, prop->m_pVarName);

		netvars[netvarName] = offset + prop->m_Offset;
	}
}
