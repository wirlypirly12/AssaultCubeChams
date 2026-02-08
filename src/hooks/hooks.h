#pragma once

using DrawEntity_t = void(__fastcall*)(int a1, int a2, int a3, int a4, unsigned int a5, int a6);


namespace hooks {
	void setup();
	void destroy();
    
    extern DrawEntity_t oDrawEntity;
    void __cdecl on_entity_render(int a1, int a2, int a3, int a4, unsigned int a5, int a6);
};


void hkDrawEntity();

