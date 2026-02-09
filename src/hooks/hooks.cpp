#include "hooks.h"
#include "minhook/MinHook.h"

#include "../structs/structs.h"

#include <iostream>

#include "gl/GL.h"

typedef void (APIENTRY* tGlDisable)(GLenum cap);
typedef void (APIENTRY* tGlEnable)(GLenum cap);
typedef void (APIENTRY* tGlColor4f)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (APIENTRY* tGlPolygonMode)(GLenum face, GLenum mode);
typedef void (APIENTRY* tGlBlendFunc)(GLenum sfactor, GLenum dfactor);

typedef void (APIENTRY* tGlPushAttrib)(GLbitfield mask);
typedef void (APIENTRY* tGlPopAttrib)(void);
typedef void (APIENTRY* tGlPushMatrix)(void);
typedef void (APIENTRY* tGlPopMatrix)(void);

//typedef Player* (__fastcall* GetEntity_t)(unsigned int client_num);
//GetEntity_t get_entity = (GetEntity_t)(0x047C8C0);

DrawEntity_t hooks::oDrawEntity = nullptr;

tGlDisable     o_glDisable     = nullptr;
tGlEnable      o_glEnable      = nullptr;
tGlColor4f     o_glColor4f     = nullptr;
tGlPolygonMode o_glPolygonMode = nullptr;
tGlBlendFunc   o_glBlendFunc   = nullptr;
tGlPushAttrib  o_glPushAttrib  = nullptr;
tGlPopAttrib   o_glPopAttrib   = nullptr;
tGlPushMatrix  o_glPushMatrix  = nullptr;
tGlPopMatrix   o_glPopMatrix   = nullptr;

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
    if (!ogl) return;

    o_glDisable     = (tGlDisable)GetProcAddress(ogl, "glDisable");
    o_glEnable      = (tGlEnable)GetProcAddress(ogl, "glEnable");
    o_glColor4f     = (tGlColor4f)GetProcAddress(ogl, "glColor4f");
    o_glPolygonMode = (tGlPolygonMode)GetProcAddress(ogl, "glPolygonMode");
    o_glBlendFunc   = (tGlBlendFunc)GetProcAddress(ogl, "glBlendFunc");

    o_glPushAttrib  = (tGlPushAttrib)GetProcAddress(ogl, "glPushAttrib");
    o_glPopAttrib   = (tGlPopAttrib)GetProcAddress(ogl, "glPopAttrib");
    o_glPushMatrix  = (tGlPushMatrix)GetProcAddress(ogl, "glPushMatrix");
    o_glPopMatrix   = (tGlPopMatrix)GetProcAddress(ogl, "glPopMatrix");
}

void hooks::destroy() {
	MH_DisableHook(MH_ALL_HOOKS);
}

void __cdecl hooks::on_entity_render(
    int a1, int a2, int a3, int a4, unsigned int a5, int a6)
{

    if (!oDrawEntity)
        return;

    if (!a1)
        return oDrawEntity(a1, a2, a3, a4, a5, a6);

    if (a3 & 0x1000)
        return oDrawEntity(a1, a2, a3, a4, a5, a6);


    Player* p = (Player*)a6;

   
    if (!p)
        return oDrawEntity(a1, a2, a3, a4, a5, a6);


    if (p->cn < 0 || p->cn >= 32)
        return oDrawEntity(a1, a2, a3, a4, a5, a6);


    o_glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    o_glPushMatrix();

    if (p->health > 0)
    {
        o_glDisable(GL_DEPTH_TEST);
        o_glEnable(GL_BLEND);
        o_glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        o_glColor4f(0.0f, 0.6f, 1.0f, 0.8f);
    }

    oDrawEntity(a1, a2, a3, a4, a5, a6);

    o_glPopMatrix();
    o_glPopAttrib();
}



void hooks::setup() {
    init_gl();

	MH_Initialize();

    MH_CreateHook(
        (LPVOID)0x0415560, // 0x015560,
        (LPVOID)hkDrawEntity,
        (LPVOID*)&oDrawEntity
    );

	MH_EnableHook(MH_ALL_HOOKS);

}

