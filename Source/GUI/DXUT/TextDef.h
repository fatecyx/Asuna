enum
{
    LB_CONTROL_ID_FIRST = DXUT_CONTROL_ID_USER,

    MAIN_TAB,

    QUICK_MSG_ENABLE,
    QUICK_MSG_TIP,

    MONSTER_COUNT_DOWN_ENABLE,
    MONSTER_COUNTDOWN_MINIMAP_SIGNAL,
    MONSTER_COUNTDOWN_SCREEN_SIGNAL,
    MONSTER_COUNTDOWN_TEAM_SIGNAL,
    MONSTER_COUNTDOWN_TIP,

    WARD_ENALBE,
    WARD_SAVE_COUNT,
    WARD_TIP,

    ZOOM_ENABLE,
    ZOOM_TIP,

    TURRET_ENABLE,
    TURRET_TIP,

    QMSG_1,
    QMSG_2,
    QMSG_3,
    QMSG_4,
    QMSG_5,
    QMSG_6,
    QMSG_7,
    QMSG_8,
    QMSG_9,

    LB_CONTROL_ID_LAST,
};

#define TAB_NAME_QUICK_MESSAGE                      L"一键消息"
#define TAB_NAME_MONSTER_COUNT_DOWN                 L"打野计时"
#define TAB_NAME_WARD_POSITION                      L"眼位监视"
#define TAB_NAME_UNLIMITED_ZOOM                     L"超远视角"
#define TAB_NAME_TURRET_COUNT_DOWN                  L"水晶计时"

#define CTRL_TEXT_QUICK_MSG_ENABLE                  L"启用一键消息"
#define CTRL_TEXT_QUICK_MSG_TIP                     L"·按下\"~\"键, 呼出一键消息面板.\n"\
                                                    L"·鼠标点击相应的消息即可发送.\n"\
                                                    L"·按\"~\"加对应的数字键发送消息."

#define CTRL_TEXT_MONSTER_COUNTDOWN_ENABLE          L"启用打野计时"
#define CTRL_TEXT_MONSTER_COUNTDOWN_MINIMAP_SIGNAL  L"小地图闪烁(仅自己可见)"
#define CTRL_TEXT_MONSTER_COUNTDOWN_SCREEN_SIGNAL   L"屏幕中间提示"
#define CTRL_TEXT_MONSTER_COUNTDOWN_TEAM_SIGNAL     L"小队自动通知"
#define CTRL_TEXT_MONSTER_COUNTDOWN_TIP             L"·自动记录红蓝buff及大小龙刷新时间.\n"\
                                                    L"·野怪刷新时间屏幕中间会有文字提醒.\n"\
                                                    L"·按F8或点击计时条小喇叭通知队友."

#define CRTL_TEXT_WARD_ENABLE                       L"启用眼位监视"
#define CRTL_TEXT_WARD_SAVE_COUNT                   L"插眼数量统计"
#define CTRL_TEXT_WARD_TIP                          L"·在迷你地图上显示眼的位置和时间.\n"\
                                                    L"·按下F7或M键打开迷你地图.\n"\
                                                    L"·地图旁边的面板会统计队友插眼的数量."

#define CRTL_TEXT_ZOOM_ENABLE                       L"启用超远视角"
#define CTRL_TEXT_ZOOM_TIP                          L"·通过鼠标滚轮改变镜头距离.\n"\
                                                    L"·通过F6键锁定/解锁."

#define CRTL_TEXT_TURRET_ENABLE                     L"启用超远视角"
#define CTRL_TEXT_TURRET_TIP                        L"·迷你地图上显示水晶的重生剩余时间.\n"\
                                                    L"·按下F7或M键打开迷你地图."

