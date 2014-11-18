#pragma once

#ifndef _XDRAWING_
#define _XDRAWING_

#include <QPaintEngine>
#include <QPaintDevice>
#include <QOpenGLPaintDevice>
#include <QPainterPath>
#include <QFont>
#include <QRawFont>
#include <QBrush>

struct _QFontOptions
{
    QFont::StyleStrategy styleStrategy;
    QFont::HintingPreference hintingPreference;
};

#include <map>
#include <cassert>
#include <cstdint>
#include <tuple>
#include <mutex>
#include <cmath>
#include <cfloat>

#endif
