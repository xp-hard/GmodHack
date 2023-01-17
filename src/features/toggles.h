#pragma once

namespace toggles {
	namespace system {
		inline bool *panic = new bool(false);
	}
	namespace misc {
		inline bool *bhop = new bool(false);
	}
	namespace visuals {
		inline bool *chams = new bool(false);
	}
};