﻿/*
---------------------------------------------------------------------------
Open Asset Import Library (assimp)
---------------------------------------------------------------------------

Copyright (c) 2006-2024, assimp team

All rights reserved.

Redistribution and use of this software in source and binary forms,
with or without modification, are permitted provided that the following
conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of the assimp team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the assimp team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
---------------------------------------------------------------------------
*/

/** @file ImporterRegistry.cpp

Central registry for all importers available. Do not edit this file
directly (unless you are adding new loaders), instead use the
corresponding preprocessor flag to selectively disable formats.
*/

#include <assimp/anim.h>
#include <assimp/BaseImporter.h>
#include <vector>
#include <cstdlib>

// ------------------------------------------------------------------------------------------------
// Importers
// (include_new_importers_here)
// ------------------------------------------------------------------------------------------------
#ifndef ASSIMP_BUILD_NO_X_IMPORTER
#include "AssetLib/X/XFileImporter.h"
#endif
#ifndef ASSIMP_BUILD_NO_AMF_IMPORTER
#include "AssetLib/AMF/AMFImporter.hpp"
#endif
#ifndef ASSIMP_BUILD_NO_3DS_IMPORTER
#include "AssetLib/3DS/3DSLoader.h"
#endif
#ifndef ASSIMP_BUILD_NO_MD3_IMPORTER
#include "AssetLib/MD3/MD3Loader.h"
#endif
#ifndef ASSIMP_BUILD_NO_MDL_IMPORTER
#include "AssetLib/MDL/MDLLoader.h"
#endif
#ifndef ASSIMP_BUILD_NO_MD2_IMPORTER
#include "AssetLib/MD2/MD2Loader.h"
#endif
#ifndef ASSIMP_BUILD_NO_PLY_IMPORTER
#include "AssetLib/Ply/PlyLoader.h"
#endif
#ifndef ASSIMP_BUILD_NO_ASE_IMPORTER
#include "AssetLib/ASE/ASELoader.h"
#endif
#ifndef ASSIMP_BUILD_NO_OBJ_IMPORTER
#include "AssetLib/Obj/ObjFileImporter.h"
#endif
#ifndef ASSIMP_BUILD_NO_HMP_IMPORTER
#include "AssetLib/HMP/HMPLoader.h"
#endif
#ifndef ASSIMP_BUILD_NO_SMD_IMPORTER
#include "AssetLib/SMD/SMDLoader.h"
#endif
#ifndef ASSIMP_BUILD_NO_MDC_IMPORTER
#include "AssetLib/MDC/MDCLoader.h"
#endif
#ifndef ASSIMP_BUILD_NO_MD5_IMPORTER
#include "AssetLib/MD5/MD5Loader.h"
#endif
#ifndef ASSIMP_BUILD_NO_STL_IMPORTER
#include "AssetLib/STL/STLLoader.h"
#endif
#ifndef ASSIMP_BUILD_NO_LWO_IMPORTER
#include "AssetLib/LWO/LWOLoader.h"
#endif
#ifndef ASSIMP_BUILD_NO_DXF_IMPORTER
#include "AssetLib/DXF/DXFLoader.h"
#endif
#ifndef ASSIMP_BUILD_NO_NFF_IMPORTER
#include "AssetLib/NFF/NFFLoader.h"
#endif
#ifndef ASSIMP_BUILD_NO_RAW_IMPORTER
#include "AssetLib/Raw/RawLoader.h"
#endif
#ifndef ASSIMP_BUILD_NO_SIB_IMPORTER
#include "AssetLib/SIB/SIBImporter.h"
#endif
#ifndef ASSIMP_BUILD_NO_OFF_IMPORTER
#include "AssetLib/OFF/OFFLoader.h"
#endif
#ifndef ASSIMP_BUILD_NO_AC_IMPORTER
#include "AssetLib/AC/ACLoader.h"
#endif
#ifndef ASSIMP_BUILD_NO_BVH_IMPORTER
#include "AssetLib/BVH/BVHLoader.h"
#endif
#ifndef ASSIMP_BUILD_NO_IRRMESH_IMPORTER
#include "AssetLib/Irr/IRRMeshLoader.h"
#endif
#ifndef ASSIMP_BUILD_NO_IRR_IMPORTER
#include "AssetLib/Irr/IRRLoader.h"
#endif
#ifndef ASSIMP_BUILD_NO_Q3D_IMPORTER
#include "AssetLib/Q3D/Q3DLoader.h"
#endif
#ifndef ASSIMP_BUILD_NO_B3D_IMPORTER
#include "AssetLib/B3D/B3DImporter.h"
#endif
#ifndef ASSIMP_BUILD_NO_COLLADA_IMPORTER
#include "AssetLib/Collada/ColladaLoader.h"
#endif
#ifndef ASSIMP_BUILD_NO_TERRAGEN_IMPORTER
#include "AssetLib/Terragen/TerragenLoader.h"
#endif
#ifndef ASSIMP_BUILD_NO_CSM_IMPORTER
#include "AssetLib/CSM/CSMLoader.h"
#endif
#ifndef ASSIMP_BUILD_NO_3D_IMPORTER
#include "AssetLib/Unreal/UnrealLoader.h"
#endif
#ifndef ASSIMP_BUILD_NO_LWS_IMPORTER
#include "AssetLib/LWS/LWSLoader.h"
#endif
#ifndef ASSIMP_BUILD_NO_OGRE_IMPORTER
#include "AssetLib/Ogre/OgreImporter.h"
#endif
#ifndef ASSIMP_BUILD_NO_OPENGEX_IMPORTER
#include "AssetLib/OpenGEX/OpenGEXImporter.h"
#endif
#ifndef ASSIMP_BUILD_NO_MS3D_IMPORTER
#include "AssetLib/MS3D/MS3DLoader.h"
#endif
#ifndef ASSIMP_BUILD_NO_COB_IMPORTER
#include "AssetLib/COB/COBLoader.h"
#endif
#ifndef ASSIMP_BUILD_NO_BLEND_IMPORTER
#include "AssetLib/Blender/BlenderLoader.h"
#endif
#ifndef ASSIMP_BUILD_NO_Q3BSP_IMPORTER
#include "AssetLib/Q3BSP/Q3BSPFileImporter.h"
#endif
#ifndef ASSIMP_BUILD_NO_NDO_IMPORTER
#include "AssetLib/NDO/NDOLoader.h"
#endif
#ifndef ASSIMP_BUILD_NO_IFC_IMPORTER
#include "AssetLib/IFC/IFCLoader.h"
#endif
#ifndef ASSIMP_BUILD_NO_XGL_IMPORTER
#include "AssetLib/XGL/XGLLoader.h"
#endif
#ifndef ASSIMP_BUILD_NO_FBX_IMPORTER
#include "AssetLib/FBX/FBXImporter.h"
#endif
#ifndef ASSIMP_BUILD_NO_ASSBIN_IMPORTER
#include "AssetLib/Assbin/AssbinLoader.h"
#endif
#if !defined(ASSIMP_BUILD_NO_GLTF_IMPORTER) && !defined(ASSIMP_BUILD_NO_GLTF1_IMPORTER)
#include "AssetLib/glTF/glTFImporter.h"
#endif
#if !defined(ASSIMP_BUILD_NO_GLTF_IMPORTER) && !defined(ASSIMP_BUILD_NO_GLTF2_IMPORTER)
#include "AssetLib/glTF2/glTF2Importer.h"
#endif
#ifndef ASSIMP_BUILD_NO_C4D_IMPORTER
#include "AssetLib/C4D/C4DImporter.h"
#endif
#ifndef ASSIMP_BUILD_NO_3MF_IMPORTER
#include "AssetLib/3MF/D3MFImporter.h"
#endif
#ifndef ASSIMP_BUILD_NO_X3D_IMPORTER
#include "AssetLib/X3D/X3DImporter.hpp"
#endif
#ifndef ASSIMP_BUILD_NO_MMD_IMPORTER
#include "AssetLib/MMD/MMDImporter.h"
#endif
#ifndef ASSIMP_BUILD_NO_M3D_IMPORTER
#include "AssetLib/M3D/M3DImporter.h"
#endif
#ifndef ASSIMP_BUILD_NO_IQM_IMPORTER
#include "AssetLib/IQM/IQMImporter.h"
#endif

namespace Assimp {

// ------------------------------------------------------------------------------------------------
void GetImporterInstanceList(std::vector<BaseImporter *> &out) {

    // Some importers may be unimplemented or otherwise unsuitable for general use
    // in their current state. Devs can set ASSIMP_ENABLE_DEV_IMPORTERS in their
    // local environment to enable them, otherwise they're left out of the registry.
#if defined(WINAPI_FAMILY) && WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP
    // not supported under uwp
    const char *envStr = std::getenv("ASSIMP_ENABLE_DEV_IMPORTERS");
#else
    const char *envStr = { "0" };
#endif
    bool devImportersEnabled = envStr && strcmp(envStr, "0");

    // Ensure no unused var warnings if all uses are #ifndef'd away below:
    (void)devImportersEnabled;

    // ----------------------------------------------------------------------------
    // Add an instance of each worker class here
    // (register_new_importers_here)
    // ----------------------------------------------------------------------------
    out.reserve(64);
//
#if (!defined ASSIMP_BUILD_NO_GLTF_IMPORTER && !defined ASSIMP_BUILD_NO_GLTF1_IMPORTER)
    out.push_back(new glTFImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_GLTF_IMPORTER && !defined ASSIMP_BUILD_NO_GLTF2_IMPORTER)
    out.push_back(new glTF2Importer());
#endif
//
#if !defined(ASSIMP_BUILD_NO_USD_IMPORTER)
    out.push_back(new USDImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_X_IMPORTER)
    out.push_back(new XFileImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_OBJ_IMPORTER)
    out.push_back(new ObjFileImporter());
#endif
#ifndef ASSIMP_BUILD_NO_AMF_IMPORTER
    out.push_back(new AMFImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_3DS_IMPORTER)
    out.push_back(new Discreet3DSImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_M3D_IMPORTER)
    out.push_back(new M3DImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_MD3_IMPORTER)
    out.push_back(new MD3Importer());
#endif
#if (!defined ASSIMP_BUILD_NO_MD2_IMPORTER)
    out.push_back(new MD2Importer());
#endif
#if (!defined ASSIMP_BUILD_NO_PLY_IMPORTER)
    out.push_back(new PLYImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_MDL_IMPORTER)
    out.push_back(new MDLImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_ASE_IMPORTER)
#if (!defined ASSIMP_BUILD_NO_3DS_IMPORTER)
    out.push_back(new ASEImporter());
#endif
#endif
#if (!defined ASSIMP_BUILD_NO_HMP_IMPORTER)
    out.push_back(new HMPImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_SMD_IMPORTER)
    out.push_back(new SMDImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_MDC_IMPORTER)
    out.push_back(new MDCImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_MD5_IMPORTER)
    out.push_back(new MD5Importer());
#endif
#if (!defined ASSIMP_BUILD_NO_STL_IMPORTER)
    out.push_back(new STLImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_LWO_IMPORTER)
    out.push_back(new LWOImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_DXF_IMPORTER)
    out.push_back(new DXFImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_NFF_IMPORTER)
    out.push_back(new NFFImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_RAW_IMPORTER)
    out.push_back(new RAWImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_SIB_IMPORTER)
    out.push_back(new SIBImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_OFF_IMPORTER)
    out.push_back(new OFFImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_AC_IMPORTER)
    out.push_back(new AC3DImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_BVH_IMPORTER)
    out.push_back(new BVHLoader());
#endif
#if (!defined ASSIMP_BUILD_NO_IRRMESH_IMPORTER)
    out.push_back(new IRRMeshImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_IRR_IMPORTER)
    out.push_back(new IRRImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_Q3D_IMPORTER)
    out.push_back(new Q3DImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_B3D_IMPORTER)
    out.push_back(new B3DImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_COLLADA_IMPORTER)
    out.push_back(new ColladaLoader());
#endif
#if (!defined ASSIMP_BUILD_NO_TERRAGEN_IMPORTER)
    out.push_back(new TerragenImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_CSM_IMPORTER)
    out.push_back(new CSMImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_3D_IMPORTER)
    out.push_back(new UnrealImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_LWS_IMPORTER)
    out.push_back(new LWSImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_OGRE_IMPORTER)
    out.push_back(new Ogre::OgreImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_OPENGEX_IMPORTER)
    out.push_back(new OpenGEX::OpenGEXImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_MS3D_IMPORTER)
    out.push_back(new MS3DImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_COB_IMPORTER)
    out.push_back(new COBImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_BLEND_IMPORTER)
    out.push_back(new BlenderImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_Q3BSP_IMPORTER)
    out.push_back(new Q3BSPFileImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_NDO_IMPORTER)
    out.push_back(new NDOImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_IFC_IMPORTER)
    out.push_back(new IFCImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_XGL_IMPORTER)
    out.push_back(new XGLImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_FBX_IMPORTER)
    out.push_back(new FBXImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_ASSBIN_IMPORTER)
    out.push_back(new AssbinImporter());
#endif
//#if (!defined ASSIMP_BUILD_NO_GLTF_IMPORTER && !defined ASSIMP_BUILD_NO_GLTF1_IMPORTER)
//    out.push_back(new glTFImporter());
//#endif
//#if (!defined ASSIMP_BUILD_NO_GLTF_IMPORTER && !defined ASSIMP_BUILD_NO_GLTF2_IMPORTER)
//    out.push_back(new glTF2Importer());
//#endif
#if (!defined ASSIMP_BUILD_NO_C4D_IMPORTER)
    out.push_back(new C4DImporter());
#endif
#if (!defined ASSIMP_BUILD_NO_3MF_IMPORTER)
    out.push_back(new D3MFImporter());
#endif
#ifndef ASSIMP_BUILD_NO_X3D_IMPORTER
    out.push_back(new X3DImporter());
#endif
#ifndef ASSIMP_BUILD_NO_MMD_IMPORTER
    out.push_back(new MMDImporter());
#endif
#ifndef ASSIMP_BUILD_NO_IQM_IMPORTER
    out.push_back(new IQMImporter());
#endif
}

/** will delete all registered importers. */
void DeleteImporterInstanceList(std::vector<BaseImporter *> &deleteList) {
    for (size_t i = 0; i < deleteList.size(); ++i) {
        delete deleteList[i];
        deleteList[i] = nullptr;
    } //for
}

} // namespace Assimp
