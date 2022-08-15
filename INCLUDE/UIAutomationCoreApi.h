// -------------------------------------------------------------
// UIAutomationCoreAPI.h
//
// UIAutomation core APIs, types and enums
//
// Copyright (c) Microsoft Corporation. All rights reserved.
// -------------------------------------------------------------


#ifndef _INC_UIAUTOMATIONCOREAPI
#define _INC_UIAUTOMATIONCOREAPI
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// --------------------------------------------------------------------------
//
// General constants and types
//
// --------------------------------------------------------------------------

// These are all in FACILITY_ITF
#define UIA_E_ELEMENTNOTENABLED      0x80040200
#define UIA_E_ELEMENTNOTAVAILABLE    0x80040201
#define UIA_E_NOCLICKABLEPOINT       0x80040202
#define UIA_E_PROXYASSEMBLYNOTLOADED 0x80040203
// The following are COR error codes, included here as a convenience
// (equivalent codes are in <corerror.h>)
#define UIA_E_INVALIDOPERATION       0x80131509 // COR_E_INVALIDOPERATION
#define UIA_E_TIMEOUT                0x80131505 // COR_E_TIMEOUT

// The following common managed exceptions are not represented here
// since they already have standard COM  error codes assigned to them
// by COM Interop:
//   ArgumentException          E_INVALIDARG
//   ArgumentNullException      - maps to ArgumentException

// Other constants
#define UiaAppendRuntimeId     3
#define UiaRootObjectId        -25

DECLARE_HANDLE(HUIANODE);
DECLARE_HANDLE(HUIAPATTERNOBJECT);
DECLARE_HANDLE(HUIATEXTRANGE);
DECLARE_HANDLE(HUIAEVENT);

enum TreeScope
{
    TreeScope_Element =       0x1,
    TreeScope_Children =      0x2,
    TreeScope_Descendants =   0x4,
    TreeScope_Parent =        0x8,
    TreeScope_Ancestors =     0x10,
    TreeScope_Subtree = TreeScope_Element | TreeScope_Children | TreeScope_Descendants
};

// --------------------------------------------------------------------------
//
// Automation Identifier GUIDs
//
// --------------------------------------------------------------------------

DEFINE_GUID(RuntimeId_Property_GUID,                                    0xa39eebfa, 0x7fba, 0x4c89, 0xb4, 0xd4, 0xb9, 0x9e, 0x2d, 0xe7, 0xd1, 0x60);
DEFINE_GUID(BoundingRectangle_Property_GUID,                            0x7bbfe8b2, 0x3bfc, 0x48dd, 0xb7, 0x29, 0xc7, 0x94, 0xb8, 0x46, 0xe9, 0xa1);
DEFINE_GUID(ProcessId_Property_GUID,                                    0x40499998, 0x9c31, 0x4245, 0xa4, 0x03, 0x87, 0x32, 0x0e, 0x59, 0xea, 0xf6);
DEFINE_GUID(ControlType_Property_GUID,                                  0xca774fea, 0x28ac, 0x4bc2, 0x94, 0xca, 0xac, 0xec, 0x6d, 0x6c, 0x10, 0xa3);
DEFINE_GUID(LocalizedControlType_Property_GUID,                         0x8763404f, 0xa1bd, 0x452a, 0x89, 0xc4, 0x3f, 0x01, 0xd3, 0x83, 0x38, 0x06);
DEFINE_GUID(Name_Property_GUID,                                         0xc3a6921b, 0x4a99, 0x44f1, 0xbc, 0xa6, 0x61, 0x18, 0x70, 0x52, 0xc4, 0x31);
DEFINE_GUID(AcceleratorKey_Property_GUID,                               0x514865df, 0x2557, 0x4cb9, 0xae, 0xed, 0x6c, 0xed, 0x08, 0x4c, 0xe5, 0x2c);
DEFINE_GUID(AccessKey_Property_GUID,                                    0x06827b12, 0xa7f9, 0x4a15, 0x91, 0x7c, 0xff, 0xa5, 0xad, 0x3e, 0xb0, 0xa7);
DEFINE_GUID(HasKeyboardFocus_Property_GUID,                             0xcf8afd39, 0x3f46, 0x4800, 0x96, 0x56, 0xb2, 0xbf, 0x12, 0x52, 0x99, 0x05);
DEFINE_GUID(IsKeyboardFocusable_Property_GUID,                          0xf7b8552a, 0x0859, 0x4b37, 0xb9, 0xcb, 0x51, 0xe7, 0x20, 0x92, 0xf2, 0x9f);
DEFINE_GUID(IsEnabled_Property_GUID,                                    0x2109427f, 0xda60, 0x4fed, 0xbf, 0x1b, 0x26, 0x4b, 0xdc, 0xe6, 0xeb, 0x3a);
DEFINE_GUID(AutomationId_Property_GUID,                                 0xc82c0500, 0xb60e, 0x4310, 0xa2, 0x67, 0x30, 0x3c, 0x53, 0x1f, 0x8e, 0xe5);
DEFINE_GUID(ClassName_Property_GUID,                                    0x157b7215, 0x894f, 0x4b65, 0x84, 0xe2, 0xaa, 0xc0, 0xda, 0x08, 0xb1, 0x6b);
DEFINE_GUID(HelpText_Property_GUID,                                     0x08555685, 0x0977, 0x45c7, 0xa7, 0xa6, 0xab, 0xaf, 0x56, 0x84, 0x12, 0x1a);
DEFINE_GUID(ClickablePoint_Property_GUID,                               0x0196903b, 0xb203, 0x4818, 0xa9, 0xf3, 0xf0, 0x8e, 0x67, 0x5f, 0x23, 0x41);
DEFINE_GUID(Culture_Property_GUID,                                      0xe2d74f27, 0x3d79, 0x4dc2, 0xb8, 0x8b, 0x30, 0x44, 0x96, 0x3a, 0x8a, 0xfb);
DEFINE_GUID(IsControlElement_Property_GUID,                             0x95f35085, 0xabcc, 0x4afd, 0xa5, 0xf4, 0xdb, 0xb4, 0x6c, 0x23, 0x0f, 0xdb);
DEFINE_GUID(IsContentElement_Property_GUID,                             0x4bda64a8, 0xf5d8, 0x480b, 0x81, 0x55, 0xef, 0x2e, 0x89, 0xad, 0xb6, 0x72);
DEFINE_GUID(LabeledBy_Property_GUID,                                    0xe5b8924b, 0xfc8a, 0x4a35, 0x80, 0x31, 0xcf, 0x78, 0xac, 0x43, 0xe5, 0x5e);
DEFINE_GUID(IsPassword_Property_GUID,                                   0xe8482eb1, 0x687c, 0x497b, 0xbe, 0xbc, 0x03, 0xbe, 0x53, 0xec, 0x14, 0x54);
DEFINE_GUID(NewNativeWindowHandle_Property_GUID,                        0x5196b33b, 0x380a, 0x4982, 0x95, 0xe1, 0x91, 0xf3, 0xef, 0x60, 0xe0, 0x24);
DEFINE_GUID(ItemType_Property_GUID,                                     0xcdda434d, 0x6222, 0x413b, 0xa6, 0x8a, 0x32, 0x5d, 0xd1, 0xd4, 0x0f, 0x39);
DEFINE_GUID(IsOffscreen_Property_GUID,                                  0x03c3d160, 0xdb79, 0x42db, 0xa2, 0xef, 0x1c, 0x23, 0x1e, 0xed, 0xe5, 0x07);
DEFINE_GUID(Orientation_Property_GUID,                                  0xa01eee62, 0x3884, 0x4415, 0x88, 0x7e, 0x67, 0x8e, 0xc2, 0x1e, 0x39, 0xba);
DEFINE_GUID(FrameworkId_Property_GUID,                                  0xdbfd9900, 0x7e1a, 0x4f58, 0xb6, 0x1b, 0x70, 0x63, 0x12, 0x0f, 0x77, 0x3b);
DEFINE_GUID(IsRequiredForForm_Property_GUID,                            0x4f5f43cf, 0x59fb, 0x4bde, 0xa2, 0x70, 0x60, 0x2e, 0x5e, 0x11, 0x41, 0xe9);
DEFINE_GUID(ItemStatus_Property_GUID,                                   0x51de0321, 0x3973, 0x43e7, 0x89, 0x13, 0x0b, 0x08, 0xe8, 0x13, 0xc3, 0x7f);
DEFINE_GUID(IsDockPatternAvailable_Property_GUID,                       0x2600a4c4, 0x2ff8, 0x4c96, 0xae, 0x31, 0x8f, 0xe6, 0x19, 0xa1, 0x3c, 0x6c);
DEFINE_GUID(IsExpandCollapsePatternAvailable_Property_GUID,             0x929d3806, 0x5287, 0x4725, 0xaa, 0x16, 0x22, 0x2a, 0xfc, 0x63, 0xd5, 0x95);
DEFINE_GUID(IsGridItemPatternAvailable_Property_GUID,                   0x5a43e524, 0xf9a2, 0x4b12, 0x84, 0xc8, 0xb4, 0x8a, 0x3e, 0xfe, 0xdd, 0x34);
DEFINE_GUID(IsGridPatternAvailable_Property_GUID,                       0x5622c26c, 0xf0ef, 0x4f3b, 0x97, 0xcb, 0x71, 0x4c, 0x08, 0x68, 0x58, 0x8b);
DEFINE_GUID(IsInvokePatternAvailable_Property_GUID,                     0x4e725738, 0x8364, 0x4679, 0xaa, 0x6c, 0xf3, 0xf4, 0x19, 0x31, 0xf7, 0x50);
DEFINE_GUID(IsMultipleViewPatternAvailable_Property_GUID,               0xff0a31eb, 0x8e25, 0x469d, 0x8d, 0x6e, 0xe7, 0x71, 0xa2, 0x7c, 0x1b, 0x90);
DEFINE_GUID(IsRangeValuePatternAvailable_Property_GUID,                 0xfda4244a, 0xeb4d, 0x43ff, 0xb5, 0xad, 0xed, 0x36, 0xd3, 0x73, 0xec, 0x4c);
DEFINE_GUID(IsScrollPatternAvailable_Property_GUID,                     0x3ebb7b4a, 0x828a, 0x4b57, 0x9d, 0x22, 0x2f, 0xea, 0x16, 0x32, 0xed, 0x0d);
DEFINE_GUID(IsScrollItemPatternAvailable_Property_GUID,                 0x1cad1a05, 0x0927, 0x4b76, 0x97, 0xe1, 0x0f, 0xcd, 0xb2, 0x09, 0xb9, 0x8a);
DEFINE_GUID(IsSelectionItemPatternAvailable_Property_GUID,              0x8becd62d, 0x0bc3, 0x4109, 0xbe, 0xe2, 0x8e, 0x67, 0x15, 0x29, 0x0e, 0x68);
DEFINE_GUID(IsSelectionPatternAvailable_Property_GUID,                  0xf588acbe, 0xc769, 0x4838, 0x9a, 0x60, 0x26, 0x86, 0xdc, 0x11, 0x88, 0xc4);
DEFINE_GUID(IsTablePatternAvailable_Property_GUID,                      0xcb83575f, 0x45c2, 0x4048, 0x9c, 0x76, 0x15, 0x97, 0x15, 0xa1, 0x39, 0xdf);
DEFINE_GUID(IsTableItemPatternAvailable_Property_GUID,                  0xeb36b40d, 0x8ea4, 0x489b, 0xa0, 0x13, 0xe6, 0x0d, 0x59, 0x51, 0xfe, 0x34);
DEFINE_GUID(IsTextPatternAvailable_Property_GUID,                       0xfbe2d69d, 0xaff6, 0x4a45, 0x82, 0xe2, 0xfc, 0x92, 0xa8, 0x2f, 0x59, 0x17);
DEFINE_GUID(IsTogglePatternAvailable_Property_GUID,                     0x78686d53, 0xfcd0, 0x4b83, 0x9b, 0x78, 0x58, 0x32, 0xce, 0x63, 0xbb, 0x5b);
DEFINE_GUID(IsTransformPatternAvailable_Property_GUID,                  0xa7f78804, 0xd68b, 0x4077, 0xa5, 0xc6, 0x7a, 0x5e, 0xa1, 0xac, 0x31, 0xc5);
DEFINE_GUID(IsValuePatternAvailable_Property_GUID,                      0x0b5020a7, 0x2119, 0x473b, 0xbe, 0x37, 0x5c, 0xeb, 0x98, 0xbb, 0xfb, 0x22);
DEFINE_GUID(IsWindowPatternAvailable_Property_GUID,                     0xe7a57bb1, 0x5888, 0x4155, 0x98, 0xdc, 0xb4, 0x22, 0xfd, 0x57, 0xf2, 0xbc);
DEFINE_GUID(Value_Value_Property_GUID,                                  0xe95f5e64, 0x269f, 0x4a85, 0xba, 0x99, 0x40, 0x92, 0xc3, 0xea, 0x29, 0x86);
DEFINE_GUID(Value_IsReadOnly_Property_GUID,                             0xeb090f30, 0xe24c, 0x4799, 0xa7, 0x05, 0x0d, 0x24, 0x7b, 0xc0, 0x37, 0xf8);
DEFINE_GUID(RangeValue_Value_Property_GUID,                             0x131f5d98, 0xc50c, 0x489d, 0xab, 0xe5, 0xae, 0x22, 0x08, 0x98, 0xc5, 0xf7);
DEFINE_GUID(RangeValue_IsReadOnly_Property_GUID,                        0x25fa1055, 0xdebf, 0x4373, 0xa7, 0x9e, 0x1f, 0x1a, 0x19, 0x08, 0xd3, 0xc4);
DEFINE_GUID(RangeValue_Minimum_Property_GUID,                           0x78cbd3b2, 0x684d, 0x4860, 0xaf, 0x93, 0xd1, 0xf9, 0x5c, 0xb0, 0x22, 0xfd);
DEFINE_GUID(RangeValue_Maximum_Property_GUID,                           0x19319914, 0xf979, 0x4b35, 0xa1, 0xa6, 0xd3, 0x7e, 0x05, 0x43, 0x34, 0x73);
DEFINE_GUID(RangeValue_LargeChange_Property_GUID,                       0xa1f96325, 0x3a3d, 0x4b44, 0x8e, 0x1f, 0x4a, 0x46, 0xd9, 0x84, 0x40, 0x19);
DEFINE_GUID(RangeValue_SmallChange_Property_GUID,                       0x81c2c457, 0x3941, 0x4107, 0x99, 0x75, 0x13, 0x97, 0x60, 0xf7, 0xc0, 0x72);
DEFINE_GUID(Scroll_HorizontalScrollPercent_Property_GUID,               0xc7c13c0e, 0xeb21, 0x47ff, 0xac, 0xc4, 0xb5, 0xa3, 0x35, 0x0f, 0x51, 0x91);
DEFINE_GUID(Scroll_HorizontalViewSize_Property_GUID,                    0x70c2e5d4, 0xfcb0, 0x4713, 0xa9, 0xaa, 0xaf, 0x92, 0xff, 0x79, 0xe4, 0xcd);
DEFINE_GUID(Scroll_VerticalScrollPercent_Property_GUID,                 0x6c8d7099, 0xb2a8, 0x4948, 0xbf, 0xf7, 0x3c, 0xf9, 0x05, 0x8b, 0xfe, 0xfb);
DEFINE_GUID(Scroll_VerticalViewSize_Property_GUID,                      0xde6a2e22, 0xd8c7, 0x40c5, 0x83, 0xba, 0xe5, 0xf6, 0x81, 0xd5, 0x31, 0x08);
DEFINE_GUID(Scroll_HorizontallyScrollable_Property_GUID,                0x8b925147, 0x28cd, 0x49ae, 0xbd, 0x63, 0xf4, 0x41, 0x18, 0xd2, 0xe7, 0x19);
DEFINE_GUID(Scroll_VerticallyScrollable_Property_GUID,                  0x89164798, 0x0068, 0x4315, 0xb8, 0x9a, 0x1e, 0x7c, 0xfb, 0xbc, 0x3d, 0xfc);
DEFINE_GUID(Selection_Selection_Property_GUID,                          0xaa6dc2a2, 0x0e2b, 0x4d38, 0x96, 0xd5, 0x34, 0xe4, 0x70, 0xb8, 0x18, 0x53);
DEFINE_GUID(Selection_CanSelectMultiple_Property_GUID,                  0x49d73da5, 0xc883, 0x4500, 0x88, 0x3d, 0x8f, 0xcf, 0x8d, 0xaf, 0x6c, 0xbe);
DEFINE_GUID(Selection_IsSelectionRequired_Property_GUID,                0xb1ae4422, 0x63fe, 0x44e7, 0xa5, 0xa5, 0xa7, 0x38, 0xc8, 0x29, 0xb1, 0x9a);
DEFINE_GUID(Grid_RowCount_Property_GUID,                                0x2a9505bf, 0xc2eb, 0x4fb6, 0xb3, 0x56, 0x82, 0x45, 0xae, 0x53, 0x70, 0x3e);
DEFINE_GUID(Grid_ColumnCount_Property_GUID,                             0xfe96f375, 0x44aa, 0x4536, 0xac, 0x7a, 0x2a, 0x75, 0xd7, 0x1a, 0x3e, 0xfc);
DEFINE_GUID(GridItem_Row_Property_GUID,                                 0x6223972a, 0xc945, 0x4563, 0x93, 0x29, 0xfd, 0xc9, 0x74, 0xaf, 0x25, 0x53);
DEFINE_GUID(GridItem_Column_Property_GUID,                              0xc774c15c, 0x62c0, 0x4519, 0x8b, 0xdc, 0x47, 0xbe, 0x57, 0x3c, 0x8a, 0xd5);
DEFINE_GUID(GridItem_RowSpan_Property_GUID,                             0x4582291c, 0x466b, 0x4e93, 0x8e, 0x83, 0x3d, 0x17, 0x15, 0xec, 0x0c, 0x5e);
DEFINE_GUID(GridItem_ColumnSpan_Property_GUID,                          0x583ea3f5, 0x86d0, 0x4b08, 0xa6, 0xec, 0x2c, 0x54, 0x63, 0xff, 0xc1, 0x09);
DEFINE_GUID(GridItem_Parent_Property_GUID,                              0x9d912252, 0xb97f, 0x4ecc, 0x85, 0x10, 0xea, 0x0e, 0x33, 0x42, 0x7c, 0x72);
DEFINE_GUID(Dock_DockPosition_Property_GUID,                            0x6d67f02e, 0xc0b0, 0x4b10, 0xb5, 0xb9, 0x18, 0xd6, 0xec, 0xf9, 0x87, 0x60);
DEFINE_GUID(ExpandCollapse_ExpandCollapseState_Property_GUID,           0x275a4c48, 0x85a7, 0x4f69, 0xab, 0xa0, 0xaf, 0x15, 0x76, 0x10, 0x00, 0x2b);
DEFINE_GUID(MultipleView_CurrentView_Property_GUID,                     0x7a81a67a, 0xb94f, 0x4875, 0x91, 0x8b, 0x65, 0xc8, 0xd2, 0xf9, 0x98, 0xe5);
DEFINE_GUID(MultipleView_SupportedViews_Property_GUID,                  0x8d5db9fd, 0xce3c, 0x4ae7, 0xb7, 0x88, 0x40, 0x0a, 0x3c, 0x64, 0x55, 0x47);
DEFINE_GUID(Window_CanMaximize_Property_GUID,                           0x64fff53f, 0x635d, 0x41c1, 0x95, 0x0c, 0xcb, 0x5a, 0xdf, 0xbe, 0x28, 0xe3);
DEFINE_GUID(Window_CanMinimize_Property_GUID,                           0xb73b4625, 0x5988, 0x4b97, 0xb4, 0xc2, 0xa6, 0xfe, 0x6e, 0x78, 0xc8, 0xc6);
DEFINE_GUID(Window_WindowVisualState_Property_GUID,                     0x4ab7905f, 0xe860, 0x453e, 0xa3, 0x0a, 0xf6, 0x43, 0x1e, 0x5d, 0xaa, 0xd5);
DEFINE_GUID(Window_WindowInteractionState_Property_GUID,                0x4fed26a4, 0x0455, 0x4fa2, 0xb2, 0x1c, 0xc4, 0xda, 0x2d, 0xb1, 0xff, 0x9c);
DEFINE_GUID(Window_IsModal_Property_GUID,                               0xff4e6892, 0x37b9, 0x4fca, 0x85, 0x32, 0xff, 0xe6, 0x74, 0xec, 0xfe, 0xed);
DEFINE_GUID(Window_IsTopmost_Property_GUID,                             0xef7d85d3, 0x0937, 0x4962, 0x92, 0x41, 0xb6, 0x23, 0x45, 0xf2, 0x40, 0x41);
DEFINE_GUID(SelectionItem_IsSelected_Property_GUID,                     0xf122835f, 0xcd5f, 0x43df, 0xb7, 0x9d, 0x4b, 0x84, 0x9e, 0x9e, 0x60, 0x20);
DEFINE_GUID(SelectionItem_SelectionContainer_Property_GUID,             0xa4365b6e, 0x9c1e, 0x4b63, 0x8b, 0x53, 0xc2, 0x42, 0x1d, 0xd1, 0xe8, 0xfb);
DEFINE_GUID(Table_RowHeaders_Property_GUID,                             0xd9e35b87, 0x6eb8, 0x4562, 0xaa, 0xc6, 0xa8, 0xa9, 0x07, 0x52, 0x36, 0xa8);
DEFINE_GUID(Table_ColumnHeaders_Property_GUID,                          0xaff1d72b, 0x968d, 0x42b1, 0xb4, 0x59, 0x15, 0x0b, 0x29, 0x9d, 0xa6, 0x64);
DEFINE_GUID(Table_RowOrColumnMajor_Property_GUID,                       0x83be75c3, 0x29fe, 0x4a30, 0x85, 0xe1, 0x2a, 0x62, 0x77, 0xfd, 0x10, 0x6e);
DEFINE_GUID(TableItem_RowHeaderItems_Property_GUID,                     0xb3f853a0, 0x0574, 0x4cd8, 0xbc, 0xd7, 0xed, 0x59, 0x23, 0x57, 0x2d, 0x97);
DEFINE_GUID(TableItem_ColumnHeaderItems_Property_GUID,                  0x967a56a3, 0x74b6, 0x431e, 0x8d, 0xe6, 0x99, 0xc4, 0x11, 0x03, 0x1c, 0x58);
DEFINE_GUID(Toggle_ToggleState_Property_GUID,                           0xb23cdc52, 0x22c2, 0x4c6c, 0x9d, 0xed, 0xf5, 0xc4, 0x22, 0x47, 0x9e, 0xde);
DEFINE_GUID(Transform_CanMove_Property_GUID,                            0x1b75824d, 0x208b, 0x4fdf, 0xbc, 0xcd, 0xf1, 0xf4, 0xe5, 0x74, 0x1f, 0x4f);
DEFINE_GUID(Transform_CanResize_Property_GUID,                          0xbb98dca5, 0x4c1a, 0x41d4, 0xa4, 0xf6, 0xeb, 0xc1, 0x28, 0x64, 0x41, 0x80);
DEFINE_GUID(Transform_CanRotate_Property_GUID,                          0x10079b48, 0x3849, 0x476f, 0xac, 0x96, 0x44, 0xa9, 0x5c, 0x84, 0x40, 0xd9);
DEFINE_GUID(ToolTipOpened_Event_GUID,                                   0x3f4b97ff, 0x2edc, 0x451d, 0xbc, 0xa4, 0x95, 0xa3, 0x18, 0x8d, 0x5b, 0x03);
DEFINE_GUID(ToolTipClosed_Event_GUID,                                   0x276d71ef, 0x24a9, 0x49b6, 0x8e, 0x97, 0xda, 0x98, 0xb4, 0x01, 0xbb, 0xcd);
DEFINE_GUID(StructureChanged_Event_GUID,                                0x59977961, 0x3edd, 0x4b11, 0xb1, 0x3b, 0x67, 0x6b, 0x2a, 0x2a, 0x6c, 0xa9);
DEFINE_GUID(MenuOpened_Event_GUID,                                      0xebe2e945, 0x66ca, 0x4ed1, 0x9f, 0xf8, 0x2a, 0xd7, 0xdf, 0x0a, 0x1b, 0x08);
DEFINE_GUID(AutomationPropertyChanged_Event_GUID,                       0x2527fba1, 0x8d7a, 0x4630, 0xa4, 0xcc, 0xe6, 0x63, 0x15, 0x94, 0x2f, 0x52);
DEFINE_GUID(AutomationFocusChanged_Event_GUID,                          0xb68a1f17, 0xf60d, 0x41a7, 0xa3, 0xcc, 0xb0, 0x52, 0x92, 0x15, 0x5f, 0xe0);
DEFINE_GUID(AsyncContentLoaded_Event_GUID,                              0x5fdee11c, 0xd2fa, 0x4fb9, 0x90, 0x4e, 0x5c, 0xbe, 0xe8, 0x94, 0xd5, 0xef);
DEFINE_GUID(MenuClosed_Event_GUID,                                      0x3cf1266e, 0x1582, 0x4041, 0xac, 0xd7, 0x88, 0xa3, 0x5a, 0x96, 0x52, 0x97);
DEFINE_GUID(LayoutInvalidated_Event_GUID,                               0xed7d6544, 0xa6bd, 0x4595, 0x9b, 0xae, 0x3d, 0x28, 0x94, 0x6c, 0xc7, 0x15);
DEFINE_GUID(Invoke_Invoked_Event_GUID,                                  0xdfd699f0, 0xc915, 0x49dd, 0xb4, 0x22, 0xdd, 0xe7, 0x85, 0xc3, 0xd2, 0x4b);
DEFINE_GUID(SelectionItem_ElementAddedToSelectionEvent_Event_GUID,      0x3c822dd1, 0xc407, 0x4dba, 0x91, 0xdd, 0x79, 0xd4, 0xae, 0xd0, 0xae, 0xc6);
DEFINE_GUID(SelectionItem_ElementRemovedFromSelectionEvent_Event_GUID,  0x097fa8a9, 0x7079, 0x41af, 0x8b, 0x9c, 0x09, 0x34, 0xd8, 0x30, 0x5e, 0x5c);
DEFINE_GUID(SelectionItem_ElementSelectedEvent_Event_GUID,              0xb9c7dbfb, 0x4ebe, 0x4532, 0xaa, 0xf4, 0x00, 0x8c, 0xf6, 0x47, 0x23, 0x3c);
DEFINE_GUID(Selection_InvalidatedEvent_Event_GUID,                      0xcac14904, 0x16b4, 0x4b53, 0x8e, 0x47, 0x4c, 0xb1, 0xdf, 0x26, 0x7b, 0xb7);
DEFINE_GUID(Text_TextSelectionChangedEvent_Event_GUID,                  0x918edaa1, 0x71b3, 0x49ae, 0x97, 0x41, 0x79, 0xbe, 0xb8, 0xd3, 0x58, 0xf3);
DEFINE_GUID(Text_TextChangedEvent_Event_GUID,                           0x4a342082, 0xf483, 0x48c4, 0xac, 0x11, 0xa8, 0x4b, 0x43, 0x5e, 0x2a, 0x84);
DEFINE_GUID(Window_WindowOpened_Event_GUID,                             0xd3e81d06, 0xde45, 0x4f2f, 0x96, 0x33, 0xde, 0x9e, 0x02, 0xfb, 0x65, 0xaf);
DEFINE_GUID(Window_WindowClosed_Event_GUID,                             0xedf141f8, 0xfa67, 0x4e22, 0xbb, 0xf7, 0x94, 0x4e, 0x05, 0x73, 0x5e, 0xe2);
DEFINE_GUID(Invoke_Pattern_GUID,                                        0xd976c2fc, 0x66ea, 0x4a6e, 0xb2, 0x8f, 0xc2, 0x4c, 0x75, 0x46, 0xad, 0x37);
DEFINE_GUID(Selection_Pattern_GUID,                                     0x66e3b7e8, 0xd821, 0x4d25, 0x87, 0x61, 0x43, 0x5d, 0x2c, 0x8b, 0x25, 0x3f);
DEFINE_GUID(Value_Pattern_GUID,                                         0x17faad9e, 0xc877, 0x475b, 0xb9, 0x33, 0x77, 0x33, 0x27, 0x79, 0xb6, 0x37);
DEFINE_GUID(RangeValue_Pattern_GUID,                                    0x18b00d87, 0xb1c9, 0x476a, 0xbf, 0xbd, 0x5f, 0x0b, 0xdb, 0x92, 0x6f, 0x63);
DEFINE_GUID(Scroll_Pattern_GUID,                                        0x895fa4b4, 0x759d, 0x4c50, 0x8e, 0x15, 0x03, 0x46, 0x06, 0x72, 0x00, 0x3c);
DEFINE_GUID(ExpandCollapse_Pattern_GUID,                                0xae05efa2, 0xf9d1, 0x428a, 0x83, 0x4c, 0x53, 0xa5, 0xc5, 0x2f, 0x9b, 0x8b);
DEFINE_GUID(Grid_Pattern_GUID,                                          0x260a2ccb, 0x93a8, 0x4e44, 0xa4, 0xc1, 0x3d, 0xf3, 0x97, 0xf2, 0xb0, 0x2b);
DEFINE_GUID(GridItem_Pattern_GUID,                                      0xf2d5c877, 0xa462, 0x4957, 0xa2, 0xa5, 0x2c, 0x96, 0xb3, 0x03, 0xbc, 0x63);
DEFINE_GUID(MultipleView_Pattern_GUID,                                  0x547a6ae4, 0x113f, 0x47c4, 0x85, 0x0f, 0xdb, 0x4d, 0xfa, 0x46, 0x6b, 0x1d);
DEFINE_GUID(Window_Pattern_GUID,                                        0x27901735, 0xc760, 0x4994, 0xad, 0x11, 0x59, 0x19, 0xe6, 0x06, 0xb1, 0x10);
DEFINE_GUID(SelectionItem_Pattern_GUID,                                 0x9bc64eeb, 0x87c7, 0x4b28, 0x94, 0xbb, 0x4d, 0x9f, 0xa4, 0x37, 0xb6, 0xef);
DEFINE_GUID(Dock_Pattern_GUID,                                          0x9cbaa846, 0x83c8, 0x428d, 0x82, 0x7f, 0x7e, 0x60, 0x63, 0xfe, 0x06, 0x20);
DEFINE_GUID(Table_Pattern_GUID,                                         0xc415218e, 0xa028, 0x461e, 0xaa, 0x92, 0x8f, 0x92, 0x5c, 0xf7, 0x93, 0x51);
DEFINE_GUID(TableItem_Pattern_GUID,                                     0xdf1343bd, 0x1888, 0x4a29, 0xa5, 0x0c, 0xb9, 0x2e, 0x6d, 0xe3, 0x7f, 0x6f);
DEFINE_GUID(Text_Pattern_GUID,                                          0x8615f05d, 0x7de5, 0x44fd, 0xa6, 0x79, 0x2c, 0xa4, 0xb4, 0x60, 0x33, 0xa8);
DEFINE_GUID(Toggle_Pattern_GUID,                                        0x0b419760, 0xe2f4, 0x43ff, 0x8c, 0x5f, 0x94, 0x57, 0xc8, 0x2b, 0x56, 0xe9);
DEFINE_GUID(Transform_Pattern_GUID,                                     0x24b46fdb, 0x587e, 0x49f1, 0x9c, 0x4a, 0xd8, 0xe9, 0x8b, 0x66, 0x4b, 0x7b);
DEFINE_GUID(ScrollItem_Pattern_GUID,                                    0x4591d005, 0xa803, 0x4d5c, 0xb4, 0xd5, 0x8d, 0x28, 0x00, 0xf9, 0x06, 0xa7);
DEFINE_GUID(Button_Control_GUID,                                        0x5a78e369, 0xc6a1, 0x4f33, 0xa9, 0xd7, 0x79, 0xf2, 0x0d, 0x0c, 0x78, 0x8e);
DEFINE_GUID(Calendar_Control_GUID,                                      0x8913eb88, 0x00e5, 0x46bc, 0x8e, 0x4e, 0x14, 0xa7, 0x86, 0xe1, 0x65, 0xa1);
DEFINE_GUID(CheckBox_Control_GUID,                                      0xfb50f922, 0xa3db, 0x49c0, 0x8b, 0xc3, 0x06, 0xda, 0xd5, 0x57, 0x78, 0xe2);
DEFINE_GUID(ComboBox_Control_GUID,                                      0x54cb426c, 0x2f33, 0x4fff, 0xaa, 0xa1, 0xae, 0xf6, 0x0d, 0xac, 0x5d, 0xeb);
DEFINE_GUID(Edit_Control_GUID,                                          0x6504a5c8, 0x2c86, 0x4f87, 0xae, 0x7b, 0x1a, 0xbd, 0xdc, 0x81, 0x0c, 0xf9);
DEFINE_GUID(Hyperlink_Control_GUID,                                     0x8a56022c, 0xb00d, 0x4d15, 0x8f, 0xf0, 0x5b, 0x6b, 0x26, 0x6e, 0x5e, 0x02);
DEFINE_GUID(Image_Control_GUID,                                         0x2d3736e4, 0x6b16, 0x4c57, 0xa9, 0x62, 0xf9, 0x32, 0x60, 0xa7, 0x52, 0x43);
DEFINE_GUID(ListItem_Control_GUID,                                      0x7b3717f2, 0x44d1, 0x4a58, 0x98, 0xa8, 0xf1, 0x2a, 0x9b, 0x8f, 0x78, 0xe2);
DEFINE_GUID(List_Control_GUID,                                          0x9b149ee1, 0x7cca, 0x4cfc, 0x9a, 0xf1, 0xca, 0xc7, 0xbd, 0xdd, 0x30, 0x31);
DEFINE_GUID(Menu_Control_GUID,                                          0x2e9b1440, 0x0ea8, 0x41fd, 0xb3, 0x74, 0xc1, 0xea, 0x6f, 0x50, 0x3c, 0xd1);
DEFINE_GUID(MenuBar_Control_GUID,                                       0xcc384250, 0x0e7b, 0x4ae8, 0x95, 0xae, 0xa0, 0x8f, 0x26, 0x1b, 0x52, 0xee);
DEFINE_GUID(MenuItem_Control_GUID,                                      0xf45225d3, 0xd0a0, 0x49d8, 0x98, 0x34, 0x9a, 0x00, 0x0d, 0x2a, 0xed, 0xdc);
DEFINE_GUID(ProgressBar_Control_GUID,                                   0x228c9f86, 0xc36c, 0x47bb, 0x9f, 0xb6, 0xa5, 0x83, 0x4b, 0xfc, 0x53, 0xa4);
DEFINE_GUID(RadioButton_Control_GUID,                                   0x3bdb49db, 0xfe2c, 0x4483, 0xb3, 0xe1, 0xe5, 0x7f, 0x21, 0x94, 0x40, 0xc6);
DEFINE_GUID(ScrollBar_Control_GUID,                                     0xdaf34b36, 0x5065, 0x4946, 0xb2, 0x2f, 0x92, 0x59, 0x5f, 0xc0, 0x75, 0x1a);
DEFINE_GUID(Slider_Control_GUID,                                        0xb033c24b, 0x3b35, 0x4cea, 0xb6, 0x09, 0x76, 0x36, 0x82, 0xfa, 0x66, 0x0b);
DEFINE_GUID(Spinner_Control_GUID,                                       0x60cc4b38, 0x3cb1, 0x4161, 0xb4, 0x42, 0xc6, 0xb7, 0x26, 0xc1, 0x78, 0x25);
DEFINE_GUID(StatusBar_Control_GUID,                                     0xd45e7d1b, 0x5873, 0x475f, 0x95, 0xa4, 0x04, 0x33, 0xe1, 0xf1, 0xb0, 0x0a);
DEFINE_GUID(Tab_Control_GUID,                                           0x38cd1f2d, 0x337a, 0x4bd2, 0xa5, 0xe3, 0xad, 0xb4, 0x69, 0xe3, 0x0b, 0xd3);
DEFINE_GUID(TabItem_Control_GUID,                                       0x2c6a634f, 0x921b, 0x4e6e, 0xb2, 0x6e, 0x08, 0xfc, 0xb0, 0x79, 0x8f, 0x4c);
DEFINE_GUID(Text_Control_GUID,                                          0xae9772dc, 0xd331, 0x4f09, 0xbe, 0x20, 0x7e, 0x6d, 0xfa, 0xf0, 0x7b, 0x0a);
DEFINE_GUID(ToolBar_Control_GUID,                                       0x8f06b751, 0xe182, 0x4e98, 0x88, 0x93, 0x22, 0x84, 0x54, 0x3a, 0x7d, 0xce);
DEFINE_GUID(ToolTip_Control_GUID,                                       0x05ddc6d1, 0x2137, 0x4768, 0x98, 0xea, 0x73, 0xf5, 0x2f, 0x71, 0x34, 0xf3);
DEFINE_GUID(Tree_Control_GUID,                                          0x7561349c, 0xd241, 0x43f4, 0x99, 0x08, 0xb5, 0xf0, 0x91, 0xbe, 0xe6, 0x11);
DEFINE_GUID(TreeItem_Control_GUID,                                      0x62c9feb9, 0x8ffc, 0x4878, 0xa3, 0xa4, 0x96, 0xb0, 0x30, 0x31, 0x5c, 0x18);
DEFINE_GUID(Custom_Control_GUID,                                        0xf29ea0c3, 0xadb7, 0x430a, 0xba, 0x90, 0xe5, 0x2c, 0x73, 0x13, 0xe6, 0xed);
DEFINE_GUID(Group_Control_GUID,                                         0xad50aa1c, 0xe8c8, 0x4774, 0xae, 0x1b, 0xdd, 0x86, 0xdf, 0x0b, 0x3b, 0xdc);
DEFINE_GUID(Thumb_Control_GUID,                                         0x701ca877, 0xe310, 0x4dd6, 0xb6, 0x44, 0x79, 0x7e, 0x4f, 0xae, 0xa2, 0x13);
DEFINE_GUID(DataGrid_Control_GUID,                                      0x84b783af, 0xd103, 0x4b0a, 0x84, 0x15, 0xe7, 0x39, 0x42, 0x41, 0x0f, 0x4b);
DEFINE_GUID(DataItem_Control_GUID,                                      0xa0177842, 0xd94f, 0x42a5, 0x81, 0x4b, 0x60, 0x68, 0xad, 0xdc, 0x8d, 0xa5);
DEFINE_GUID(Document_Control_GUID,                                      0x3cd6bb6f, 0x6f08, 0x4562, 0xb2, 0x29, 0xe4, 0xe2, 0xfc, 0x7a, 0x9e, 0xb4);
DEFINE_GUID(SplitButton_Control_GUID,                                   0x7011f01f, 0x4ace, 0x4901, 0xb4, 0x61, 0x92, 0x0a, 0x6f, 0x1c, 0xa6, 0x50);
DEFINE_GUID(Window_Control_GUID,                                        0xe13a7242, 0xf462, 0x4f4d, 0xae, 0xc1, 0x53, 0xb2, 0x8d, 0x6c, 0x32, 0x90);
DEFINE_GUID(Pane_Control_GUID,                                          0x5c2b3f5b, 0x9182, 0x42a3, 0x8d, 0xec, 0x8c, 0x04, 0xc1, 0xee, 0x63, 0x4d);
DEFINE_GUID(Header_Control_GUID,                                        0x5b90cbce, 0x78fb, 0x4614, 0x82, 0xb6, 0x55, 0x4d, 0x74, 0x71, 0x8e, 0x67);
DEFINE_GUID(HeaderItem_Control_GUID,                                    0xe6bc12cb, 0x7c8e, 0x49cf, 0xb1, 0x68, 0x4a, 0x93, 0xa3, 0x2b, 0xeb, 0xb0);
DEFINE_GUID(Table_Control_GUID,                                         0x773bfa0e, 0x5bc4, 0x4deb, 0x92, 0x1b, 0xde, 0x7b, 0x32, 0x06, 0x22, 0x9e);
DEFINE_GUID(TitleBar_Control_GUID,                                      0x98aa55bf, 0x3bb0, 0x4b65, 0x83, 0x6e, 0x2e, 0xa3, 0x0d, 0xbc, 0x17, 0x1f);
DEFINE_GUID(Separator_Control_GUID,                                     0x8767eba3, 0x2a63, 0x4ab0, 0xac, 0x8d, 0xaa, 0x50, 0xe2, 0x3d, 0xe9, 0x78);
DEFINE_GUID(Text_AnimationStyle_Attribute_GUID,                         0x628209f0, 0x7c9a, 0x4d57, 0xbe, 0x64, 0x1f, 0x18, 0x36, 0x57, 0x1f, 0xf5);
DEFINE_GUID(Text_BackgroundColor_Attribute_GUID,                        0xfdc49a07, 0x583d, 0x4f17, 0xad, 0x27, 0x77, 0xfc, 0x83, 0x2a, 0x3c, 0x0b);
DEFINE_GUID(Text_BulletStyle_Attribute_GUID,                            0xc1097c90, 0xd5c4, 0x4237, 0x97, 0x81, 0x3b, 0xec, 0x8b, 0xa5, 0x4e, 0x48);
DEFINE_GUID(Text_CapStyle_Attribute_GUID,                               0xfb059c50, 0x92cc, 0x49a5, 0xba, 0x8f, 0x0a, 0xa8, 0x72, 0xbb, 0xa2, 0xf3);
DEFINE_GUID(Text_Culture_Attribute_GUID,                                0xc2025af9, 0xa42d, 0x4ced, 0xa1, 0xfb, 0xc6, 0x74, 0x63, 0x15, 0x22, 0x2e);
DEFINE_GUID(Text_FontName_Attribute_GUID,                               0x64e63ba8, 0xf2e5, 0x476e, 0xa4, 0x77, 0x17, 0x34, 0xfe, 0xaa, 0xf7, 0x26);
DEFINE_GUID(Text_FontSize_Attribute_GUID,                               0xdc5eeeff, 0x0506, 0x4673, 0x93, 0xf2, 0x37, 0x7e, 0x4a, 0x8e, 0x01, 0xf1);
DEFINE_GUID(Text_FontWeight_Attribute_GUID,                             0x6fc02359, 0xb316, 0x4f5f, 0xb4, 0x01, 0xf1, 0xce, 0x55, 0x74, 0x18, 0x53);
DEFINE_GUID(Text_ForegroundColor_Attribute_GUID,                        0x72d1c95d, 0x5e60, 0x471a, 0x96, 0xb1, 0x6c, 0x1b, 0x3b, 0x77, 0xa4, 0x36);
DEFINE_GUID(Text_HorizontalTextAlignment_Attribute_GUID,                0x04ea6161, 0xfba3, 0x477a, 0x95, 0x2a, 0xbb, 0x32, 0x6d, 0x02, 0x6a, 0x5b);
DEFINE_GUID(Text_IndentationFirstLine_Attribute_GUID,                   0x206f9ad5, 0xc1d3, 0x424a, 0x81, 0x82, 0x6d, 0xa9, 0xa7, 0xf3, 0xd6, 0x32);
DEFINE_GUID(Text_IndentationLeading_Attribute_GUID,                     0x5cf66bac, 0x2d45, 0x4a4b, 0xb6, 0xc9, 0xf7, 0x22, 0x1d, 0x28, 0x15, 0xb0);
DEFINE_GUID(Text_IndentationTrailing_Attribute_GUID,                    0x97ff6c0f, 0x1ce4, 0x408a, 0xb6, 0x7b, 0x94, 0xd8, 0x3e, 0xb6, 0x9b, 0xf2);
DEFINE_GUID(Text_IsHidden_Attribute_GUID,                               0x360182fb, 0xbdd7, 0x47f6, 0xab, 0x69, 0x19, 0xe3, 0x3f, 0x8a, 0x33, 0x44);
DEFINE_GUID(Text_IsItalic_Attribute_GUID,                               0xfce12a56, 0x1336, 0x4a34, 0x96, 0x63, 0x1b, 0xab, 0x47, 0x23, 0x93, 0x20);
DEFINE_GUID(Text_IsReadOnly_Attribute_GUID,                             0xa738156b, 0xca3e, 0x495e, 0x95, 0x14, 0x83, 0x3c, 0x44, 0x0f, 0xeb, 0x11);
DEFINE_GUID(Text_IsSubscript_Attribute_GUID,                            0xf0ead858, 0x8f53, 0x413c, 0x87, 0x3f, 0x1a, 0x7d, 0x7f, 0x5e, 0x0d, 0xe4);
DEFINE_GUID(Text_IsSuperscript_Attribute_GUID,                          0xda706ee4, 0xb3aa, 0x4645, 0xa4, 0x1f, 0xcd, 0x25, 0x15, 0x7d, 0xea, 0x76);
DEFINE_GUID(Text_MarginBottom_Attribute_GUID,                           0x7ee593c4, 0x72b4, 0x4cac, 0x92, 0x71, 0x3e, 0xd2, 0x4b, 0x0e, 0x4d, 0x42);
DEFINE_GUID(Text_MarginLeading_Attribute_GUID,                          0x9e9242d0, 0x5ed0, 0x4900, 0x8e, 0x8a, 0xee, 0xcc, 0x03, 0x83, 0x5a, 0xfc);
DEFINE_GUID(Text_MarginTop_Attribute_GUID,                              0x683d936f, 0xc9b9, 0x4a9a, 0xb3, 0xd9, 0xd2, 0x0d, 0x33, 0x31, 0x1e, 0x2a);
DEFINE_GUID(Text_MarginTrailing_Attribute_GUID,                         0xaf522f98, 0x999d, 0x40af, 0xa5, 0xb2, 0x01, 0x69, 0xd0, 0x34, 0x20, 0x02);
DEFINE_GUID(Text_OutlineStyles_Attribute_GUID,                          0x5b675b27, 0xdb89, 0x46fe, 0x97, 0x0c, 0x61, 0x4d, 0x52, 0x3b, 0xb9, 0x7d);
DEFINE_GUID(Text_OverlineColor_Attribute_GUID,                          0x83ab383a, 0xfd43, 0x40da, 0xab, 0x3e, 0xec, 0xf8, 0x16, 0x5c, 0xbb, 0x6d);
DEFINE_GUID(Text_OverlineStyle_Attribute_GUID,                          0x0a234d66, 0x617e, 0x427f, 0x87, 0x1d, 0xe1, 0xff, 0x1e, 0x0c, 0x21, 0x3f);
DEFINE_GUID(Text_StrikethroughColor_Attribute_GUID,                     0xbfe15a18, 0x8c41, 0x4c5a, 0x9a, 0x0b, 0x04, 0xaf, 0x0e, 0x07, 0xf4, 0x87);
DEFINE_GUID(Text_StrikethroughStyle_Attribute_GUID,                     0x72913ef1, 0xda00, 0x4f01, 0x89, 0x9c, 0xac, 0x5a, 0x85, 0x77, 0xa3, 0x07);
DEFINE_GUID(Text_Tabs_Attribute_GUID,                                   0x2e68d00b, 0x92fe, 0x42d8, 0x89, 0x9a, 0xa7, 0x84, 0xaa, 0x44, 0x54, 0xa1);
DEFINE_GUID(Text_TextFlowDirections_Attribute_GUID,                     0x8bdf8739, 0xf420, 0x423e, 0xaf, 0x77, 0x20, 0xa5, 0xd9, 0x73, 0xa9, 0x07);
DEFINE_GUID(Text_UnderlineColor_Attribute_GUID,                         0xbfa12c73, 0xfde2, 0x4473, 0xbf, 0x64, 0x10, 0x36, 0xd6, 0xaa, 0x0f, 0x45);
DEFINE_GUID(Text_UnderlineStyle_Attribute_GUID,                         0x5f3b21c0, 0xede4, 0x44bd, 0x9c, 0x36, 0x38, 0x53, 0x03, 0x8c, 0xbf, 0xeb);

DEFINE_GUID(SID_IsUIAutomationObject,                                   0xb96fdb85, 0x7204, 0x4724, 0x84, 0x2b, 0xc7, 0x05, 0x9d, 0xed, 0xb9, 0xd0);

// --------------------------------------------------------------------------
//
// Error handling
//
// --------------------------------------------------------------------------

BOOL WINAPI UiaGetErrorDescription(BSTR * pDescription);

// --------------------------------------------------------------------------
//
// Conditions
//
// --------------------------------------------------------------------------

enum ConditionType
{
    ConditionType_True = 0,
    ConditionType_False = 1,
    ConditionType_Property = 2,
    ConditionType_And = 3,
    ConditionType_Or = 4,
    ConditionType_Not = 5,
};

struct UiaCondition
{
    ConditionType ConditionType;
};

enum PropertyConditionFlags
{
    PropertyConditionFlags_None = 0x00,
    PropertyConditionFlags_IgnoreCase = 0x01,
};

struct UiaPropertyCondition
{
    ConditionType ConditionType;
    PROPERTYID PropertyId;
    VARIANT Value;
    PropertyConditionFlags Flags;
};

struct UiaAndOrCondition
{
    ConditionType ConditionType;
    UiaCondition ** ppConditions; // ptr to array-of-ptrs to conditions
    int cConditions;
};

struct UiaNotCondition
{
    ConditionType ConditionType;
    UiaCondition * pCondition;
};


// --------------------------------------------------------------------------
//
// Cache request/response
//
// --------------------------------------------------------------------------

enum AutomationElementMode
{
    AutomationElementMode_None,
    AutomationElementMode_Full
};

struct UiaCacheRequest
{
    UiaCondition *  pViewCondition;
    TreeScope       Scope;

    PROPERTYID *    pProperties;
    int             cProperties;
    PATTERNID *     pPatterns;
    int             cPatterns;
    AutomationElementMode automationElementMode;
};

HRESULT WINAPI UiaHUiaNodeFromVariant(VARIANT * pvar, HUIANODE *phnode);
HRESULT WINAPI UiaHPatternObjectFromVariant(VARIANT * pvar, HUIAPATTERNOBJECT *phobj);
HRESULT WINAPI UiaHTextRangeFromVariant(VARIANT * pvar, HUIATEXTRANGE *phtextrange);

// --------------------------------------------------------------------------
//
// UiaNode methods
//
// --------------------------------------------------------------------------

// Used by UiaGetUpdatedCache
enum NormalizeState
{
    NormalizeState_None,    // Don't normalize
    NormalizeState_View,    // Normalize against condition in UiaCacheRequest
    NormalizeState_Custom   // Normalize against supplied condition
};

struct UiaFindParams
{
    int MaxDepth;
    BOOL FindFirst;
    BOOL ExcludeRoot;
    UiaCondition * pFindCondition;
};

BOOL WINAPI UiaNodeRelease(HUIANODE hnode);

HRESULT WINAPI UiaGetPropertyValue(HUIANODE hnode, PROPERTYID propertyId, VARIANT * pValue);
HRESULT WINAPI UiaGetPatternProvider(HUIANODE hnode, PATTERNID patternId, HUIAPATTERNOBJECT * phobj);
HRESULT WINAPI UiaGetRuntimeId(HUIANODE hnode, SAFEARRAY ** pruntimeId);
HRESULT WINAPI UiaSetFocus(HUIANODE hnode);
HRESULT WINAPI UiaNavigate(HUIANODE hnode, NavigateDirection direction, UiaCondition * pCondition, UiaCacheRequest * pRequest, SAFEARRAY ** ppRequestedData, BSTR * ppTreeStructure);
HRESULT WINAPI UiaGetUpdatedCache(HUIANODE hnode, UiaCacheRequest * pRequest, NormalizeState normalizeState, UiaCondition * pNormalizeCondition, SAFEARRAY ** ppRequestedData, BSTR * ppTreeStructure);
HRESULT WINAPI UiaFind(HUIANODE hnode, UiaFindParams * pParams, UiaCacheRequest * pRequest, SAFEARRAY ** ppRequestedData, SAFEARRAY ** ppOffsets, SAFEARRAY ** ppTreeStructures);

HRESULT WINAPI UiaNodeFromPoint(double x, double y, UiaCacheRequest * pRequest, SAFEARRAY ** ppRequestedData, BSTR * ppTreeStructure);
HRESULT WINAPI UiaNodeFromFocus(UiaCacheRequest * pRequest, SAFEARRAY ** ppRequestedData, BSTR * ppTreeStructure);
HRESULT WINAPI UiaNodeFromHandle(HWND hwnd, HUIANODE * phnode);
HRESULT WINAPI UiaNodeFromProvider(IRawElementProviderSimple * pProvider, HUIANODE * phnode);
HRESULT WINAPI UiaGetRootNode(HUIANODE * phnode);


#ifdef __cplusplus
inline void UiaRectSetEmpty(UiaRect & rc)
{
    rc.left = 0;
    rc.top = 0;
    rc.width = 0;
    rc.height = 0;
}

inline bool UiaRectIsEmpty(const UiaRect & rc)
{
    return rc.width <= 0 || rc.height <= 0;
}
#endif

// --------------------------------------------------------------------------
//
// Client-side provider support
//
// --------------------------------------------------------------------------

enum ProviderType
{
    ProviderType_BaseHwnd,
    ProviderType_Proxy,
    ProviderType_NonClientArea,
};

typedef SAFEARRAY * WINAPI UiaProviderCallback(HWND hwnd, ProviderType providerType);

void WINAPI UiaRegisterProviderCallback(UiaProviderCallback * pCallback);


// --------------------------------------------------------------------------
//
// Identifier mapping
//
// --------------------------------------------------------------------------

enum AutomationIdentifierType
{
    AutomationIdentifierType_Property,
    AutomationIdentifierType_Pattern,
    AutomationIdentifierType_Event,
    AutomationIdentifierType_ControlType,
    AutomationIdentifierType_TextAttribute
};

int WINAPI UiaLookupId(AutomationIdentifierType type, const GUID* pGuid);

HRESULT WINAPI UiaGetReservedNotSupportedValue(IUnknown **punkNotSupportedValue);
HRESULT WINAPI UiaGetReservedMixedAttributeValue(IUnknown **punkMixedAttributeValue);

// --------------------------------------------------------------------------
//
// Event methods
//
// --------------------------------------------------------------------------

//
// Event structs and enums
//

enum EventArgsType
{
    EventArgsType_Simple,
    EventArgsType_PropertyChanged,
    EventArgsType_StructureChanged,
    EventArgsType_AsyncContentLoaded,
    EventArgsType_WindowClosed,
};

enum StructureChangeType
{
    StructureChangeType_ChildAdded,
    StructureChangeType_ChildRemoved,
    StructureChangeType_ChildrenInvalidated,
    StructureChangeType_ChildrenBulkAdded,
    StructureChangeType_ChildrenBulkRemoved,
    StructureChangeType_ChildrenReordered,
};

enum AsyncContentLoadedState
{
    AsyncContentLoadedState_Beginning,
    AsyncContentLoadedState_Progress,
    AsyncContentLoadedState_Completed
};

struct UiaEventArgs
{
    EventArgsType Type;
    int EventId;
};

struct UiaPropertyChangedEventArgs
{
    EventArgsType Type;
    int EventId;
    PROPERTYID PropertyId;
    VARIANT OldValue;
    VARIANT NewValue;
};

struct UiaStructureChangedEventArgs
{
    EventArgsType Type;
    int EventId;
    StructureChangeType StructureChangeType;
    int * pRuntimeId;
    int cRuntimeIdLen;
};

struct UiaAsyncContentLoadedEventArgs
{
    EventArgsType Type;
    int EventId;
    AsyncContentLoadedState AsyncContentLoadedState;
    double PercentComplete;
};

struct UiaWindowClosedEventArgs
{
    EventArgsType Type;
    int EventId;
    int * pRuntimeId;
    int cRuntimeIdLen;
};

//
// Provider Event APIs
//
BOOL WINAPI UiaClientsAreListening();
HRESULT WINAPI UiaRaiseAutomationPropertyChangedEvent(IRawElementProviderSimple * pProvider, PROPERTYID id, VARIANT oldValue, VARIANT newValue);
HRESULT WINAPI UiaRaiseAutomationEvent(IRawElementProviderSimple * pProvider, EVENTID id);
HRESULT WINAPI UiaRaiseStructureChangedEvent(IRawElementProviderSimple * pProvider, StructureChangeType structureChangeType, int * pRuntimeId, int cRuntimeIdLen);
HRESULT WINAPI UiaRaiseAsyncContentLoadedEvent(IRawElementProviderSimple * pProvider, AsyncContentLoadedState asyncContentLoadedState, double percentComplete);

//
// Client Event APIs
//
typedef void WINAPI UiaEventCallback(UiaEventArgs * pArgs, SAFEARRAY * pRequestedData, BSTR pTreeStructure);
HRESULT WINAPI UiaAddEvent(HUIANODE hnode, EVENTID eventId, UiaEventCallback * pCallback, TreeScope scope, PROPERTYID * pProperties, int cProperties, UiaCacheRequest * pRequest, HUIAEVENT * phEvent);
HRESULT WINAPI UiaRemoveEvent(HUIAEVENT hEvent);
HRESULT WINAPI UiaEventAddWindow(HUIAEVENT hEvent, HWND hwnd);
HRESULT WINAPI UiaEventRemoveWindow(HUIAEVENT hEvent, HWND hwnd);


// --------------------------------------------------------------------------
//
// Pattern methods
//
// --------------------------------------------------------------------------

HRESULT WINAPI DockPattern_SetDockPosition(HUIAPATTERNOBJECT hobj, DockPosition dockPosition);
HRESULT WINAPI ExpandCollapsePattern_Collapse(HUIAPATTERNOBJECT hobj);
HRESULT WINAPI ExpandCollapsePattern_Expand(HUIAPATTERNOBJECT hobj);
HRESULT WINAPI GridPattern_GetItem(HUIAPATTERNOBJECT hobj, int row, int column, HUIANODE * pResult);
HRESULT WINAPI InvokePattern_Invoke(HUIAPATTERNOBJECT hobj);
HRESULT WINAPI MultipleViewPattern_GetViewName(HUIAPATTERNOBJECT hobj, int viewId, BSTR * ppStr);
HRESULT WINAPI MultipleViewPattern_SetCurrentView(HUIAPATTERNOBJECT hobj, int viewId);
HRESULT WINAPI RangeValuePattern_SetValue(HUIAPATTERNOBJECT hobj, double val);
HRESULT WINAPI ScrollItemPattern_ScrollIntoView(HUIAPATTERNOBJECT hobj);
HRESULT WINAPI ScrollPattern_Scroll(HUIAPATTERNOBJECT hobj, ScrollAmount horizontalAmount, ScrollAmount verticalAmount);
HRESULT WINAPI ScrollPattern_SetScrollPercent(HUIAPATTERNOBJECT hobj, double horizontalPercent, double verticalPercent);
HRESULT WINAPI SelectionItemPattern_AddToSelection(HUIAPATTERNOBJECT hobj);
HRESULT WINAPI SelectionItemPattern_RemoveFromSelection(HUIAPATTERNOBJECT hobj);
HRESULT WINAPI SelectionItemPattern_Select(HUIAPATTERNOBJECT hobj);
HRESULT WINAPI TogglePattern_Toggle(HUIAPATTERNOBJECT hobj);
HRESULT WINAPI TransformPattern_Move(HUIAPATTERNOBJECT hobj, double x, double y);
HRESULT WINAPI TransformPattern_Resize(HUIAPATTERNOBJECT hobj, double width, double height);
HRESULT WINAPI TransformPattern_Rotate(HUIAPATTERNOBJECT hobj, double degrees);
HRESULT WINAPI ValuePattern_SetValue(HUIAPATTERNOBJECT hobj, LPCWSTR pVal);
HRESULT WINAPI WindowPattern_Close(HUIAPATTERNOBJECT hobj);
HRESULT WINAPI WindowPattern_SetWindowVisualState(HUIAPATTERNOBJECT hobj, WindowVisualState state);
HRESULT WINAPI WindowPattern_WaitForInputIdle(HUIAPATTERNOBJECT hobj, int milliseconds, BOOL * pResult);

HRESULT WINAPI TextPattern_GetSelection(HUIAPATTERNOBJECT hobj, SAFEARRAY** pRetVal);
HRESULT WINAPI TextPattern_GetVisibleRanges(HUIAPATTERNOBJECT hobj, SAFEARRAY** pRetVal);
HRESULT WINAPI TextPattern_RangeFromChild(HUIAPATTERNOBJECT hobj, HUIANODE hnodeChild, HUIATEXTRANGE* pRetVal);
HRESULT WINAPI TextPattern_RangeFromPoint(HUIAPATTERNOBJECT hobj, UiaPoint point, HUIATEXTRANGE* pRetVal);
HRESULT WINAPI TextPattern_get_DocumentRange(HUIAPATTERNOBJECT hobj, HUIATEXTRANGE* pRetVal);
HRESULT WINAPI TextPattern_get_SupportedTextSelection(HUIAPATTERNOBJECT hobj, SupportedTextSelection* pRetVal);
HRESULT WINAPI TextRange_Clone(HUIATEXTRANGE hobj, HUIATEXTRANGE* pRetVal);
HRESULT WINAPI TextRange_Compare(HUIATEXTRANGE hobj, HUIATEXTRANGE range, BOOL* pRetVal);
HRESULT WINAPI TextRange_CompareEndpoints(HUIATEXTRANGE hobj, TextPatternRangeEndpoint endpoint, HUIATEXTRANGE targetRange, TextPatternRangeEndpoint targetEndpoint, int* pRetVal);
HRESULT WINAPI TextRange_ExpandToEnclosingUnit(HUIATEXTRANGE hobj, TextUnit unit);
HRESULT WINAPI TextRange_GetAttributeValue(HUIATEXTRANGE hobj, TEXTATTRIBUTEID attributeId, VARIANT * pRetVal);
HRESULT WINAPI TextRange_FindAttribute(HUIATEXTRANGE hobj, TEXTATTRIBUTEID attributeId, VARIANT val, BOOL backward, HUIATEXTRANGE * pRetVal);
HRESULT WINAPI TextRange_FindText(HUIATEXTRANGE hobj, BSTR text, BOOL backward, BOOL ignoreCase, HUIATEXTRANGE* pRetVal);
HRESULT WINAPI TextRange_GetBoundingRectangles(HUIATEXTRANGE hobj, SAFEARRAY** pRetVal);
HRESULT WINAPI TextRange_GetEnclosingElement(HUIATEXTRANGE hobj, HUIANODE* pRetVal);
HRESULT WINAPI TextRange_GetText(HUIATEXTRANGE hobj, int maxLength, BSTR* pRetVal);
HRESULT WINAPI TextRange_Move(HUIATEXTRANGE hobj, TextUnit unit, int count, int* pRetVal);
HRESULT WINAPI TextRange_MoveEndpointByUnit(HUIATEXTRANGE hobj, TextPatternRangeEndpoint endpoint, TextUnit unit, int count, int* pRetVal);
HRESULT WINAPI TextRange_MoveEndpointByRange(HUIATEXTRANGE hobj, TextPatternRangeEndpoint endpoint, HUIATEXTRANGE targetRange, TextPatternRangeEndpoint targetEndpoint);
HRESULT WINAPI TextRange_Select(HUIATEXTRANGE hobj);
HRESULT WINAPI TextRange_AddToSelection(HUIATEXTRANGE hobj);
HRESULT WINAPI TextRange_RemoveFromSelection(HUIATEXTRANGE hobj);
HRESULT WINAPI TextRange_ScrollIntoView(HUIATEXTRANGE hobj, BOOL alignToTop);
HRESULT WINAPI TextRange_GetChildren(HUIATEXTRANGE hobj, SAFEARRAY** pRetVal);

BOOL WINAPI UiaPatternRelease(HUIAPATTERNOBJECT hobj);
BOOL WINAPI UiaTextRangeRelease(HUIATEXTRANGE hobj);


// --------------------------------------------------------------------------
//
// Provider methods
// 
// --------------------------------------------------------------------------

LRESULT WINAPI UiaReturnRawElementProvider(HWND hwnd, WPARAM wParam, LPARAM lParam, IRawElementProviderSimple * el);
HRESULT WINAPI UiaHostProviderFromHwnd(HWND hwnd, IRawElementProviderSimple ** pProvider);

// --------------------------------------------------------------------------
//
// Other APIs...
//
// --------------------------------------------------------------------------

BOOL WINAPI UiaHasServerSideProvider(HWND hwnd);

#ifdef __cplusplus
}
#endif


#endif // !_INC_UIAUTOMATIONCOREAPI