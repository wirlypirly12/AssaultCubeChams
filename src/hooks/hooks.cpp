#include "hooks.h"
#include "minhook/MinHook.h"


#include <iostream>

#include "gl/GL.h"

typedef void (APIENTRY* tGlDisable)(GLenum cap);
typedef void (APIENTRY* tGlEnable)(GLenum cap);
typedef void (APIENTRY* tGlSetColor)(float, float, float, float);

tGlSetColor o_glColor4f = nullptr;
tGlDisable o_glDisable = nullptr;
tGlEnable o_glEnable = nullptr;

DrawEntity_t hooks::oDrawEntity = nullptr;


__declspec(naked) void hkDrawEntity()
{
    __asm
    {
        push ebp
        mov ebp, esp
        pushad
        sub esp, 16
        movdqu[esp], xmm3

        push[ebp + 20]
        push[ebp + 16]
        push[ebp + 12]
        push[ebp + 8]
        sub esp, 4
        movss[esp], xmm3
        push ecx

        call hooks::on_entity_render
        add esp, 24

        movdqu xmm3, [esp]
        add esp, 16
        popad
        pop ebp

        jmp[hooks::oDrawEntity]
    }
}

void init_gl()
{
    HMODULE ogl = GetModuleHandleA("opengl32.dll");


    o_glDisable = (tGlDisable)GetProcAddress(ogl, "glDisable");
    o_glEnable = (tGlEnable)GetProcAddress(ogl, "glEnable");
    o_glColor4f = (tGlSetColor)GetProcAddress(ogl, "glColor4f");
}



void hooks::destroy() {
	MH_DisableHook(MH_ALL_HOOKS);
}

void __cdecl hooks::on_entity_render(int a1, float a2, int a3, int a4, unsigned int a5, int a6)
{
    if (!hooks::oDrawEntity) {
        MessageBoxA(NULL, "oDrawEntity is NULL!", "Error", MB_OK);
        return;
    }


    if (!a1 || !a6)
        return oDrawEntity(a1, a2, a3, a4, a5, a6);

   

    o_glDisable(GL_DEPTH_TEST);
    o_glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

    oDrawEntity(a1, a2, a3, a4, a5, a6);

    o_glEnable(GL_DEPTH_TEST);

}

void hooks::setup() {
    init_gl();

	MH_Initialize();

    MH_CreateHook(
        (LPVOID)0x0415560,
        (LPVOID)hkDrawEntity,
        (LPVOID*)&oDrawEntity
    );

	MH_EnableHook(MH_ALL_HOOKS);
}

