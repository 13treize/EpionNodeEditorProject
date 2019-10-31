// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、
// または、参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する



// プログラムに必要な追加ヘッダーをここで参照してください
#include	<sstream>
#include	<string>
#include	<utility>
#include	<memory>
#include	<vector>

#include	"../../../imgui\\imconfig.h"
#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"
#include	<cereal/cereal.hpp>
#include	<cereal/types/polymorphic.hpp>

#include	"node_data.h"
#include	"../EpionNodeShaderTool/epion_physics/epion_collider.h"
#include	"../EpionNodeShaderTool/epion_string.h"
