//
// Copyright (c) 2019 The nanoFramework project contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//

#include "Graphics.h"
#include "TouchPanel_native.h"


static const CLR_RT_MethodHandler method_lookup[] =
{
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    Library_touch_native_Ink::SetInkRegion___STATIC__VOID__U4__I4__I4__I4__I4__I4__I4__I4__GraphicsBitmap,
    Library_touch_native_Ink::ResetInkRegion___STATIC__VOID,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    Library_touch_native_TouchCollectorConfiguration::EnableTouchCollection___STATIC__VOID__I4__I4__I4__I4__I4__GraphicsBitmap,
    Library_touch_native_TouchCollectorConfiguration::GetTouchPoints___STATIC__VOID__BYREF_I4__SZARRAY_I2__SZARRAY_I2,
    Library_touch_native_TouchCollectorConfiguration::GetTouchInput___STATIC__VOID__TouchTouchCollectorConfigurationTouchInput__BYREF_I4__BYREF_I4__BYREF_I4,
    Library_touch_native_TouchCollectorConfiguration::SetTouchInput___STATIC__VOID__TouchTouchCollectorConfigurationTouchInput__I4__I4__I4,
    NULL,
    Library_touch_native_TouchEventProcessor::ProcessEvent___NativeBaseEvent__U4__U4__mscorlibSystemDateTime,
    NULL,
    NULL,
    NULL,
    Library_touch_native_TouchPanel::SetCalibration___VOID__I4__SZARRAY_I2__SZARRAY_I2__SZARRAY_I2__SZARRAY_I2,
    Library_touch_native_TouchPanel::GetCalibrationPointCount___VOID__BYREF_I4,
    Library_touch_native_TouchPanel::StartCalibration___VOID,
    Library_touch_native_TouchPanel::GetCalibrationPoint___VOID__I4__BYREF_I4__BYREF_I4,
    Library_touch_native_TouchPanel::EnableInternal___VOID__BOOLEAN,
    NULL, 
};

const CLR_RT_NativeAssemblyData g_CLR_AssemblyNative_Touch =
{
    "UI.Touch", 
    0x2D4E2DCC,
    method_lookup,
       { 1, 0, 2, 2 }  // Dummy version to stop [-Werror=missing-field-initializers]
};

const CLR_RT_NativeAssemblyData g_CLR_AssemblyNative_nanoFramework_Runtime_Events =
{
    "nanoFramework.Runtime.Events",
    0xBFF88292,
    method_lookup,
    { 1, 0, 2, 2 }
};