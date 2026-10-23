// cihazlar.h: İki ayrı namespace'te AYNI isimli fonksiyon: isim çakışması olmaz.
#pragma once   // include guard'ın kısa yazımı (#ifndef/#define/#endif ile aynı işi görür)

#include "telemetri.h"   // main.cpp zaten telemetri.h'yi de include ediyor: iki kez gelir, guard sayesinde sorun yok

namespace sensor {
void yaz();
}

namespace motor {
void yaz();
}
