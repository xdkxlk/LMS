#pragma once

//当在我的好友中双击选择一个人
#define WM_ONE_USER_SELECT (WM_USER+1)
//当有消息来的时候
#define WM_SOCKET_NEW_MESSAGE (WM_USER+2)
//当有SOCKET事件的时候
#define WM_SOCKET (WM_USER+3)
//当有当有一个新朋友成功添加的时候
#define WM_NEW_FRIEND_ADDED (WM_USER+4)
//更新朋友状态
#define WM_UPDAT_FRIEND_STATUS (WM_USER+5)
//删除朋友
#define WM_DEL_FRIEND (WM_USER+6)
//禁用输入框
#define WM_DISABLE_INPUT (WM_USER+7)
//后台静默删除朋友
#define WM_DEL_FRIEND_BACKGROUND (WM_USER+8)
//当在我的群组中双击选择一群组
#define WM_ONE_GROUP_SELECT (WM_USER+9)
//加入群组成功
#define WM_JOIN_GROUP (WM_USER+10)
//退出群组
#define WM_QUIT_GROUP (WM_USER+11)