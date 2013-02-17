var key_util = {};

key_util.category_table = {
  CAT_TAB_WINDOW: 'tab_and_window_shortcuts',
  CAT_ADDRESS: 'address_bar_shortcuts',
  CAT_WEB_PAGE: 'webpage_shortcuts',
  CAT_TEXT: 'text_shortcuts',
  CAT_BOSS_KEY: 'boss_key',
  CAT_QUICK_LAUNCH: 'quick_launch_shortcuts',
  CAT_FILL_FORM: 'fill_form_shortcuts',
  CAT_MUTE: 'mute_shortcuts',
  CAT_CHROME_FEATURE: 'google_chrome_feature_shortcuts'
}

key_util.function_table_record = function() {
  this.id = 0;
  this.functionName = '';
  this.category = 0;
  this.isSupport = false;
  this.chromeKey = '';
  this.browser360Key = '';
  this.maxthonKey = '';
  this.ttKey = '';
  this.sogouKey = '';
};

key_util.browser = {
  browser360Key: 'browser360_key',
  maxthonKey: 'maxthon_key',
  ttKey: 'tt_key',
  sogouKey: 'sogou_key',
  ie6Key: 'ie6_key',
  ie7Key: 'ie7_key',
  ie8Key: 'ie8_key',
  operaKey: 'opera_key',
  safariKey: 'safari_key',
  firefoxKey: 'firefox_key'
}

key_util.function_table = [];
key_util.function_table[1] = {
  id: 1, function_name: 'new_window_short',
  function_description: 'new_window',
  category: key_util.category_table.CAT_TAB_WINDOW,
  isQuickly: false, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+N',
  browser360_key: 'Ctrl+N', maxthon_key: '',
  tt_key: '', sogou_key: 'Ctrl+M, Ctrl+Shift+N',
  ie6_key: 'Ctrl+N', ie7_key: 'Ctrl+N',
  ie8_key: 'Ctrl+N', opera_key: 'Ctrl+N',
  safari_key: 'Ctrl+N', firefox_key: 'Ctrl+N'
};
key_util.function_table[2] = {
  id: 2, function_name: 'new_tab_short',
  function_description: 'new_tab',
  category: key_util.category_table.CAT_TAB_WINDOW,
  isQuickly: false, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+T',
  browser360_key: 'Ctrl+T', maxthon_key: 'Ctrl+T',
  tt_key: 'Ctrl+N', sogou_key: 'Ctrl+T',
  ie6_key: '', ie7_key: 'Ctrl+T',
  ie8_key: 'Ctrl+T', opera_key: 'Ctrl+T',
  safari_key: 'Ctrl+T', firefox_key: 'Ctrl+T'
};
key_util.function_table[3] = {
  id: 3, function_name: 'new_incognito_window_short',
  function_description: 'new_incognito_window',
  category: key_util.category_table.CAT_TAB_WINDOW,
  isQuickly: false, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+Shift+N',
  browser360_key: '', maxthon_key: '',
  tt_key: '', sogou_key: '',
  ie6_key: '', ie7_key: '',
  ie8_key: 'Ctrl+Shift+P', opera_key: '',
  safari_key: '', firefox_key: 'Ctrl+Shift+P'
};
key_util.function_table[4] = {
  id: 4, function_name: 'open_file_short',
  function_description: 'open_file',
  category: key_util.category_table.CAT_TAB_WINDOW,
  isQuickly: true, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+O', chrome_virtual_key: '17+79',
  browser360_key: 'Ctrl+O', maxthon_key: 'Ctrl+O',
  tt_key: 'Ctrl+O', sogou_key: 'Ctrl+O',
  ie6_key: 'Ctrl+O, Ctrl+L', ie7_key: 'Ctrl+O, Ctrl+L',
  ie8_key: 'Ctrl+O, Ctrl+L', opera_key: 'Ctrl+O',
  safari_key: 'Ctrl+O', firefox_key: 'Ctrl+O'
};
key_util.function_table[5] = {
  id: 5, function_name: 'reopen_closed_tab_short',
  function_description: 'reopen_closed_tab',
  category: key_util.category_table.CAT_TAB_WINDOW,
  isQuickly: true, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+Shift+T', chrome_virtual_key: '17+16+84',
  browser360_key: 'Ctrl+Shift+T', maxthon_key: '',
  tt_key: '', sogou_key: '',
  ie6_key: '', ie7_key: '',
  ie8_key: 'Ctrl+Shift+T', opera_key: 'Ctrl+Alt+Z',
  safari_key: 'Ctrl+Z', firefox_key: 'Ctrl+Shift+T'
};
key_util.function_table[6] = {
  id: 6, function_name: 'switch_tab_short',
  function_description: 'switch_tab',
  category: key_util.category_table.CAT_TAB_WINDOW,
  isQuickly: false, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+1...Ctrl+8',
  browser360_key: '', maxthon_key: '',
  tt_key: '', sogou_key: '',
  ie6_key: '', ie7_key: 'Ctrl+1...Ctrl+8',
  ie8_key: 'Ctrl+1...Ctrl+8', opera_key: '',
  safari_key: '', firefox_key: 'Ctrl+1...Ctrl+8'
};
key_util.function_table[7] = {
  id: 7, function_name: 'last_tab_short',
  function_description: 'last_tab',
  category: key_util.category_table.CAT_TAB_WINDOW,
  isQuickly: false, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+9',
  browser360_key: '', maxthon_key: '',
  tt_key: '', sogou_key: '',
  ie6_key: '', ie7_key: 'Ctrl+9',
  ie8_key: 'Ctrl+9', opera_key: '',
  safari_key: '', firefox_key: 'Ctrl+9'
};
key_util.function_table[8] = {
  id: 8, function_name: 'next_tab_short',
  function_description: 'next_tab',
  category: key_util.category_table.CAT_TAB_WINDOW,
  isQuickly: true, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+Tab, Ctrl+PageDown', chrome_virtual_key: '17+9, 17+34',
  browser360_key: 'F3, Alt+Down', maxthon_key: 'F3',
  tt_key: 'F8', sogou_key: 'F3',
  ie6_key: '', ie7_key: 'Ctrl+Tab',
  ie8_key: 'Ctrl+Tab', opera_key: 'Ctrl+Tab, Ctrl+F6',
  safari_key: 'Ctrl+Tab', firefox_key: 'Ctrl+PageDown, Ctrl+Tab'
};
key_util.function_table[9] = {
  id: 9, function_name: 'prev_tab_short',
  function_description: 'prev_tab',
  category: key_util.category_table.CAT_TAB_WINDOW,
  isQuickly: true, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+Shift+Tab, Ctrl+PageUp',
  chrome_virtual_key: '17+16+9, 17+33',
  browser360_key: 'F2, Alt+Up', maxthon_key: 'F2',
  tt_key: 'F7', sogou_key: 'F2',
  ie6_key: '', ie7_key: 'Ctrl+Shift+Tab',
  ie8_key: 'Ctrl+Shift+Tab', opera_key: 'Ctrl+Shift+Tab, Ctrl+Shift+F6',
  safari_key: 'Ctrl+Shift+Tab', firefox_key: 'Ctrl+PageUp, Ctrl+Shift+Tab'
};
key_util.function_table[10] = {
  id: 10, function_name: 'close_window_short',
  function_description: 'close_window',
  category: key_util.category_table.CAT_TAB_WINDOW,
  isQuickly: true, isSystem: true, isSupport: true,
  chrome_key: 'Alt+F4', chrome_virtual_key: '18+115',
  browser360_key: 'Alt+F4', maxthon_key: 'Alt+F4',
  tt_key: 'Alt+F4', sogou_key: 'Alt+F4',
  ie6_key: 'Alt+F4', ie7_key: 'Alt+F4',
  ie8_key: 'Alt+F4', opera_key: 'Ctrl+Shift+W, Alt+F4',
  safari_key: 'Ctrl+Shift+W, Alt+F4', firefox_key: 'Ctrl+Shift+W, Alt+F4'
};
key_util.function_table[11] = {
  id: 11, function_name: 'close_tab_short',
  function_description: 'close_tab',
  category: key_util.category_table.CAT_TAB_WINDOW,
  isQuickly: true, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+W, Ctrl+F4', chrome_virtual_key: '17+87, 17+115',
  browser360_key: 'Ctrl+F4, Ctrl+W', maxthon_key: 'Ctrl+F4, Ctrl+W',
  tt_key: 'Ctrl+F4, Ctrl+W', sogou_key: 'Ctrl+F4, Ctrl+W',
  ie6_key: '', ie7_key: 'Ctrl+F4, Ctrl+W',
  ie8_key: 'Ctrl+F4, Ctrl+W', opera_key: 'Ctrl+F4, Ctrl+W',
  safari_key: 'Ctrl+F4, Ctrl+W', firefox_key: 'Ctrl+F4, Ctrl+W'
};
key_util.function_table[12] = {
  id: 12, function_name: 'history_back_short',
  function_description: 'history_back',
  category: key_util.category_table.CAT_TAB_WINDOW,
  isQuickly: false, isSystem: true, isSupport: true,
  chrome_key: 'Backspace, Alt+Left',
  browser360_key: 'Alt+Left, Backspace', maxthon_key: 'Alt+Left, Backspace',
  tt_key: 'Alt+Left, Backspace', sogou_key: 'Alt+Left, Backspace',
  ie6_key: 'Alt+Left, Backspace', ie7_key: 'Alt+Left, Backspace',
  ie8_key: 'Alt+Left, Backspace', opera_key: 'Ctrl+Left, Alt+Left, Backspace',
  safari_key: 'Alt+Left, Backspace', firefox_key: 'Alt+Left, Backspace'
};
key_util.function_table[13] = {
  id: 13, function_name: 'history_forward_short',
  function_description: 'history_forward',
  category: key_util.category_table.CAT_TAB_WINDOW,
  isQuickly: false, isSystem: true, isSupport: false,
  chrome_key: 'Shift+Backspace, Alt+Right',
  browser360_key: 'Alt+Right', maxthon_key: 'Alt+Right',
  tt_key: 'Alt+Right', sogou_key: 'Alt+Right',
  ie6_key: 'Alt+Right, Shift+Backspace', ie7_key: 'Alt+Right, Shift+Backspace',
  ie8_key: 'Alt+Right, Shift+Backspace',
  opera_key: 'Ctrl+Right, Alt+Right, Shift+Backspace',
  safari_key: 'Alt+Right, Shift+Backspace',
  firefox_key: 'Alt+Right, Shift+Backspace'
};
key_util.function_table[14] = {
  id: 14, function_name: 'history_home_short',
  function_description: 'history_home',
  category: key_util.category_table.CAT_TAB_WINDOW,
  isQuickly: true, isSystem: true, isSupport: true,
  chrome_key: 'Alt+Home', chrome_virtual_key: '18+36',
  browser360_key: 'Alt+Home', maxthon_key: 'Alt+Home',
  tt_key: 'Alt+Home', sogou_key: 'Alt+Home',
  ie6_key: 'Alt+Home', ie7_key: 'Alt+Home',
  ie8_key: 'Alt+Home', opera_key: 'Alt+Home, Alt+Space',
  safari_key: 'Ctrl+Shift+H', firefox_key: 'Alt+Home'
};
key_util.function_table[15] = {
  id: 15, function_name: 'bookmarks_bar_always_show_short',
  function_description: 'bookmarks_bar_always_show',
  category: key_util.category_table.CAT_TAB_WINDOW,
  isQuickly: true, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+Shift+B', chrome_virtual_key: '17+16+66, 17+115',
  browser360_key: 'Ctrl+B', maxthon_key: '',
  tt_key: '', sogou_key: '',
  ie6_key: '', ie7_key: '',
  ie8_key: '', opera_key: 'Ctrl+B',
  safari_key: 'Ctrl+Shift+B', firefox_key: 'Ctrl+B'
};
key_util.function_table[16] = {
  id: 16, function_name: 'history_menu_short',
  function_description: 'history_menu',
  category: key_util.category_table.CAT_TAB_WINDOW,
  isQuickly: false, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+H',
  browser360_key: 'Ctrl+H', maxthon_key: 'Ctrl+H',
  tt_key: 'Ctrl+H', sogou_key: 'Ctrl+H',
  ie6_key: 'Ctrl+H', ie7_key: 'Ctrl+H',
  ie8_key: 'Ctrl+H', opera_key: 'Ctrl+H',
  safari_key: 'Ctrl+H', firefox_key: 'Ctrl+H'
};
key_util.function_table[17] = {
  id: 17, function_name: 'show_downloads_short',
  function_description: 'show_downloads',
  category: key_util.category_table.CAT_TAB_WINDOW,
  isQuickly: false, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+J',
  browser360_key: '', maxthon_key: '',
  tt_key: '', sogou_key: '',
  ie6_key: '', ie7_key: '',
  ie8_key: '', opera_key: 'Ctrl+J',
  safari_key: 'Ctrl+Alt+L', firefox_key: 'Ctrl+J'
};
key_util.function_table[18] = {
  id: 18, function_name: 'task_manager_short',
  function_description: 'task_manager',
  category: key_util.category_table.CAT_CHROME_FEATURE,
  isQuickly: true, isSystem: true, isSupport: true,
  chrome_key: 'Shift+Esc', chrome_virtual_key: '16+27',
  browser360_key: '', maxthon_key: '',
  tt_key: '', sogou_key: '',
  ie6_key: '', ie7_key: '',
  ie8_key: '', opera_key: '',
  safari_key: '', firefox_key: ''
};
key_util.function_table[19] = {
  id: 19, function_name: 'browser_toolbar_short',
  function_description: 'browser_toolbar',
  category: key_util.category_table.CAT_CHROME_FEATURE,
  isQuickly: false, isSystem: true, isSupport: true,
  chrome_key: 'Shift+Alt+T',
  browser360_key: '', maxthon_key: '',
  tt_key: '', sogou_key: '',
  ie6_key: '', ie7_key: '',
  ie8_key: '', opera_key: '',
  safari_key: '', firefox_key: ''
};
key_util.function_table[20] = {
  id: 20, function_name: 'context_menu_short',
  function_description: 'context_menu',
  category: key_util.category_table.CAT_WEB_PAGE,
  isQuickly: false, isSystem: true, isSupport: true,
  chrome_key: 'Shift+F10',
  browser360_key: 'Shift+F10', maxthon_key: 'Shift+F10',
  tt_key: 'Shift+F10', sogou_key: 'Shift+F10',
  ie6_key: 'Shift+F10', ie7_key: 'Shift+F10',
  ie8_key: 'Shift+F10', opera_key: 'Shift+F10',
  safari_key: 'Shift+F10', firefox_key: 'Shift+F10'
};
key_util.function_table[21] = {
  id: 21, function_name: 'dev_tools_short',
  function_description: 'dev_tools',
  category: key_util.category_table.CAT_TAB_WINDOW,
  isQuickly: true, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+Shift+I', chrome_virtual_key: '17+16+73',
  browser360_key: '', maxthon_key: '',
  tt_key: '', sogou_key: '',
  ie6_key: '', ie7_key: '',
  ie8_key: 'F12', opera_key: '',
  safari_key: '', firefox_key: ''
};
key_util.function_table[22] = {
  id: 22, function_name: 'clear_browsing_data_short',
  function_description: 'clear_browsing_data',
  category: key_util.category_table.CAT_TAB_WINDOW,
  isQuickly: true, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+Shift+Delete', chrome_virtual_key: '17+16+46',
  browser360_key: '', maxthon_key: '',
  tt_key: 'Alt+X', sogou_key: 'Alt+X',
  ie6_key: '', ie7_key: '',
  ie8_key: 'Ctrl+Shift+Delete', opera_key: '',
  safari_key: '', firefox_key: 'Ctrl+Shift+Delete'
};
key_util.function_table[23] = {
  id: 23, function_name: 'help_short',
  function_description: 'help',
  category: key_util.category_table.CAT_TAB_WINDOW,
  isQuickly: false, isSystem: true, isSupport: true,
  chrome_key: 'F1',
  browser360_key: 'F1', maxthon_key: 'F1',
  tt_key: 'F1', sogou_key: 'F1',
  ie6_key: 'F1', ie7_key: 'F1',
  ie8_key: 'F1', opera_key: 'F1',
  safari_key: 'F1', firefox_key: 'F1'
};
key_util.function_table[24] = {
  id: 24, function_name: 'open_location_short',
  function_description: 'open_location',
  category: key_util.category_table.CAT_ADDRESS,
  isQuickly: true, isSystem: true, isSupport: true,
  chrome_key: 'F6, Ctrl+L, Alt+D', chrome_virtual_key: '117, 17+76, 18+68',
  browser360_key: 'F6, Alt+D', maxthon_key: 'F6, Alt+D',
  tt_key: 'F6, Alt+D', sogou_key: 'Ctrl+L, F6, Alt+D',
  ie6_key: 'F6, Alt+D', ie7_key: 'F6, Alt+D',
  ie8_key: 'F6, Alt+D', opera_key: 'F8, Ctrl+L, Alt+D',
  safari_key: 'Alt+D, F6, Ctrl+L', firefox_key: 'Alt+D, F6, Ctrl+L'
};
key_util.function_table[25] = {
  id: 25, function_name: 'edit_search_web_short',
  function_description: 'edit_search_web',
  category: key_util.category_table.CAT_ADDRESS,
  isQuickly: true, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+K, Ctrl+E', chrome_virtual_key: '17+75, 17+69',
  browser360_key: '', maxthon_key: 'Ctrl+E',
  tt_key: '', sogou_key: 'Ctrl+E',
  ie6_key: 'Ctrl+E', ie7_key: 'Ctrl+E',
  ie8_key: 'Ctrl+E', opera_key: 'Ctrl+E',
  safari_key: 'Ctrl+E', firefox_key: 'Ctrl+E'
};
key_util.function_table[26] = {
  id: 26, function_name: 'print_short',
  function_description: 'print',
  category: key_util.category_table.CAT_WEB_PAGE,
  isQuickly: false, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+P', chrome_virtual_key: '17+80',
  browser360_key: 'Ctrl+P', maxthon_key: 'Ctrl+P',
  tt_key: 'Ctrl+P', sogou_key: 'Ctrl+P',
  ie6_key: 'Ctrl+P', ie7_key: 'Ctrl+P',
  ie8_key: 'Ctrl+P', opera_key: 'Ctrl+P',
  safari_key: 'Ctrl+P', firefox_key: 'Ctrl+P'
};
key_util.function_table[27] = {
  id: 27, function_name: 'save_page_short',
  function_description: 'save_page',
  category: key_util.category_table.CAT_WEB_PAGE,
  isQuickly: false, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+S',
  browser360_key: 'Ctrl+S', maxthon_key: 'Ctrl+S',
  tt_key: 'Ctrl+S', sogou_key: 'Ctrl+S',
  ie6_key: '', ie7_key: 'Ctrl+S',
  ie8_key: 'Ctrl+S', opera_key: 'Ctrl+S',
  safari_key: 'Ctrl+S', firefox_key: 'Ctrl+S'
  },
key_util.function_table[28] = {
  id: 28, function_name: 'reload_menu_short',
  function_description: 'reload_menu',
  category: key_util.category_table.CAT_WEB_PAGE,
  isQuickly: true, isSystem: true, isSupport: true,
  chrome_key: 'F5, Ctrl+R', chrome_virtual_key: '116, 17+82',
  browser360_key: 'F5', maxthon_key: 'F5',
  tt_key: 'F5', sogou_key: 'F5',
  ie6_key: 'F5', ie7_key: 'F5',
  ie8_key: 'F5', opera_key: 'F5, Ctrl+R',
  safari_key: 'F5, Ctrl+R', firefox_key: 'F5, Ctrl+R'
};
key_util.function_table[29] = {
  id: 29, function_name: 'stop_menu_short',
  function_description: 'stop_menu',
  category: key_util.category_table.CAT_WEB_PAGE,
  isQuickly: true, isSystem: true, isSupport: true,
  chrome_key: 'Esc', chrome_virtual_key: '27',
  browser360_key: 'Esc', maxthon_key: 'Esc',
  tt_key: 'Esc', sogou_key: 'Esc',
  ie6_key: 'Esc', ie7_key: 'Esc',
  ie8_key: 'Esc', opera_key: 'Esc',
  safari_key: 'Esc', firefox_key: 'Esc'
};
key_util.function_table[30] = {
  id: 30, function_name: 'edit_find_short',
  function_description: 'edit_find',
  category: key_util.category_table.CAT_WEB_PAGE,
  isQuickly: false, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+F',
  browser360_key: 'Ctrl+F', maxthon_key: 'Ctrl+F',
  tt_key: 'Ctrl+F', sogou_key: 'Ctrl+F',
  ie6_key: 'Ctrl+F', ie7_key: 'Ctrl+F',
  ie8_key: 'Ctrl+F', opera_key: 'Ctrl+F',
  safari_key: 'Ctrl+F', firefox_key: 'Ctrl+F'
};
key_util.function_table[31] = {
  id: 31, function_name: 'edit_find_next_short',
  function_description: 'edit_find_next',
  category: key_util.category_table.CAT_WEB_PAGE,
  isQuickly: false, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+G, F3, Enter',
  browser360_key: 'Enter', maxthon_key: 'Enter',
  tt_key: '', sogou_key: 'Enter',
  ie6_key: 'Enter', ie7_key: 'Enter',
  ie8_key: 'Enter', opera_key: 'Ctrl+G, F3, Enter',
  safari_key: 'Ctrl+G, F3, Enter', firefox_key: 'Ctrl+G, F3, Enter'
};
key_util.function_table[32] = {
  id: 32, function_name: 'edit_find_previous_short',
  function_description: 'edit_find_previous',
  category: key_util.category_table.CAT_WEB_PAGE,
  isQuickly: false, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+Shift+G, Shift+Enter, Shift+F3',
  browser360_key: 'Shift+Enter', maxthon_key: 'Shift+Enter',
  tt_key: '', sogou_key: 'Shift+Enter',
  ie6_key: '', ie7_key: '',
  ie8_key: 'Shift+Enter', opera_key: 'Ctrl+Shift+G, Shift+Enter, Shift+F3',
  safari_key: 'Ctrl+Shift+G, Shift+Enter, Shift+F3',
  firefox_key: 'Ctrl+Shift+G, Shift+Enter, Shift+F3'
};
key_util.function_table[33] = {
  id: 33, function_name: 'reload_ignoring_cache_menu_short',
  function_description: 'reload_ignoring_cache_menu',
  category: key_util.category_table.CAT_WEB_PAGE,
  isQuickly: true, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+F5, Shift+F5', chrome_virtual_key: '17+116, 16+115',
  browser360_key: 'Ctrl+F5, Shift+F5', maxthon_key: 'Ctrl+F5, Shift+F5',
  tt_key: 'Ctrl+F5, Shift+F5', sogou_key: 'Ctrl+F5, Shift+F5',
  ie6_key: 'Ctrl+F5, Ctrl+R', ie7_key: 'Ctrl+F5, Ctrl+R',
  ie8_key: 'Ctrl+F5, Ctrl+R', opera_key: 'Alt+F5, Ctrl+Shift+R',
  safari_key: 'Ctrl+R', firefox_key: 'Ctrl+F5, Ctrl+Shift+R'
};
key_util.function_table[34] = {
  id: 34, function_name: 'view_source_short',
  function_description: 'view_source',
  category: key_util.category_table.CAT_WEB_PAGE,
  isQuickly: true, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+U', chrome_virtual_key: '17+85',
  browser360_key: '', maxthon_key: '',
  tt_key: '', sogou_key: '',
  ie6_key: '', ie7_key: '',
  ie8_key: '', opera_key: 'Ctrl+F3',
  safari_key: 'Ctrl+Alt+U', firefox_key: 'Ctrl+U'
};
key_util.function_table[35] = {
  id: 35, function_name: 'bookmark_current_page_short',
  function_description: 'bookmark_current_page',
  category: key_util.category_table.CAT_WEB_PAGE,
  isQuickly: true, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+D', chrome_virtual_key: '17+68',
  browser360_key: 'Ctrl+D', maxthon_key: 'Ctrl+D',
  tt_key: 'Ctrl+D', sogou_key: 'Ctrl+D',
  ie6_key: 'Ctrl+D', ie7_key: 'Ctrl+D',
  ie8_key: 'Ctrl+D', opera_key: 'Ctrl+D',
  safari_key: 'Ctrl+D', firefox_key: 'Ctrl+D'
};
key_util.function_table[36] = {
  id: 36, function_name: 'bookmark_all_tabs_short',
  function_description: 'bookmark_all_tabs',
  category: key_util.category_table.CAT_WEB_PAGE,
  isQuickly: true, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+Shift+D', chrome_virtual_key: '17+16+68',
  browser360_key: '', maxthon_key: '',
  tt_key: '', sogou_key: 'Ctrl+Shift+D',
  ie6_key: '', ie7_key: '',
  ie8_key: '', opera_key: '',
  safari_key: '', firefox_key: 'Ctrl+Shift+D'
};
key_util.function_table[37] = {
  id: 37, function_name: 'enter_fullscreen_short',
  function_description: 'enter_fullscreen',
  category: key_util.category_table.CAT_WEB_PAGE,
  isQuickly: true, isSystem: true, isSupport: true,
  chrome_key: 'F11', chrome_virtual_key: '122',
  browser360_key: 'F11', maxthon_key: 'F11',
  tt_key: 'F11', sogou_key: 'F11',
  ie6_key: 'F11', ie7_key: 'F11',
  ie8_key: 'F11', opera_key: 'F11',
  safari_key: '', firefox_key: 'F11'
};
key_util.function_table[38] = {
  id: 38, function_name: 'text_bigger_short',
  function_description: 'text_bigger',
  category: key_util.category_table.CAT_WEBPAGE,
  isQuickly: false, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl++',
  browser360_key: 'Ctrl++', maxthon_key: 'Ctrl++',
  tt_key: '', sogou_key: 'Ctrl++',
  ie6_key: '', ie7_key: 'Ctrl++',
  ie8_key: 'Ctrl++', opera_key: 'Ctrl++,+',
  safari_key: 'Ctrl++', firefox_key: 'Ctrl++'
};
key_util.function_table[39] = {
  id: 39, function_name: 'text_smaller_short',
  function_description: 'text_smaller',
  category: key_util.category_table.CAT_WEBPAGE,
  isQuickly: false, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+-',
  browser360_key: 'Ctrl+-', maxthon_key: 'Ctrl+-',
  tt_key: '', sogou_key: 'Ctrl+-',
  ie6_key: '', ie7_key: 'Ctrl+-',
  ie8_key: 'Ctrl+-', opera_key: 'Ctrl+-,-',
  safari_key: 'Ctrl+-', firefox_key: 'Ctrl+-'
};
key_util.function_table[40] = {
  id: 40, function_name: 'text_default_short',
  function_description: 'text_default',
  category: key_util.category_table.CAT_WEBPAGE,
  isQuickly: false, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+0',
  browser360_key: 'Ctrl+/', maxthon_key: 'Ctrl+8',
  tt_key: '', sogou_key: 'Ctrl+0',
  ie6_key: '', ie7_key: 'Ctrl+0',
  ie8_key: 'Ctrl+0', opera_key: 'Ctrl+0,*',
  safari_key: 'Ctrl+0', firefox_key: 'Ctrl+0'
};
key_util.function_table[41] = {
  id: 41, function_name: 'scroll_down_short',
  function_description: 'scroll_down',
  category: key_util.category_table.CAT_WEB_PAGE,
  isQuickly: false, isSystem: true, isSupport: true,
  chrome_key: 'Space',
  browser360_key: 'Space', maxthon_key: 'Space',
  tt_key: 'Space', sogou_key: 'Space',
  ie6_key: 'Space', ie7_key: 'Space',
  ie8_key: 'Space', opera_key: 'Space',
  safari_key: 'Space', firefox_key: 'Space'
};
key_util.function_table[42] = {
  id: 42, function_name: 'goto_top_short',
  function_description: 'goto_top',
  category: key_util.category_table.CAT_WEB_PAGE,
  isQuickly: true, isSystem: true, isSupport: true,
  chrome_key: 'Home', chrome_virtual_key: '36',
  browser360_key: 'Home', maxthon_key: 'Home',
  tt_key: 'Home', sogou_key: 'Home',
  ie6_key: 'Home', ie7_key: 'Home',
  ie8_key: 'Home', opera_key: 'Home',
  safari_key: 'Home', firefox_key: 'Home'
};
key_util.function_table[43] = {
  id: 43, function_name: 'goto_bottom_short',
  function_description: 'goto_bottom',
  category: key_util.category_table.CAT_WEB_PAGE,
  isQuickly: true, isSystem: true, isSupport: true,
  chrome_key: 'End', chrome_virtual_key: '35',
  browser360_key: 'End', maxthon_key: 'End',
  tt_key: 'End', sogou_key: 'End',
  ie6_key: 'End', ie7_key: 'End',
  ie8_key: 'End', opera_key: 'End',
  safari_key: 'End', firefox_key: 'End'
};
key_util.function_table[44] = {
  id: 44, function_name: 'copy_short',
  function_description: 'copy',
  category: key_util.category_table.CAT_TEXT,
  isQuickly: false, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+C',
  browser360_key: 'Ctrl+C', maxthon_key: 'Ctrl+C',
  tt_key: 'Ctrl+C', sogou_key: 'Ctrl+C',
  ie6_key: 'Ctrl+C', ie7_key: 'Ctrl+C',
  ie8_key: 'Ctrl+C', opera_key: 'Ctrl+C',
  safari_key: 'Ctrl+C', firefox_key: 'Ctrl+C'
};
key_util.function_table[45] = {
  id: 45, function_name: 'paste_short',
  function_description: 'paste',
  category: key_util.category_table.CAT_TEXT,
  isQuickly: false, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+V, Shift+Insert',
  browser360_key: 'Ctrl+V, Shift+Insert', maxthon_key: 'Ctrl+V, Shift+Insert',
  tt_key: 'Ctrl+V, Shift+Insert', sogou_key: 'Ctrl+V, Shift+Insert',
  ie6_key: 'Ctrl+V, Shift+Insert', ie7_key: 'Ctrl+V, Shift+Insert',
  ie8_key: 'Ctrl+V, Shift+Insert', opera_key: 'Ctrl+V, Shift+Insert',
  safari_key: 'Ctrl+V, Shift+Insert', firefox_key: 'Ctrl+V, Shift+Insert'
};
key_util.function_table[46] = {
  id: 46, function_name: 'paste_match_style_short',
  function_description: 'paste_match_style',
  category: key_util.category_table.CAT_TEXT,
  isQuickly: true, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+Shift+V', chrome_virtual_key: '17+16+86',
  browser360_key: '', maxthon_key: '',
  tt_key: '', sogou_key: '',
  ie6_key: '', ie7_key: '',
  ie8_key: '', opera_key: '',
  safari_key: '', firefox_key: ''
};
key_util.function_table[47] = {
  id: 47, function_name: 'cut_short',
  function_description: 'cut',
  category: key_util.category_table.CAT_TEXT,
  isQuickly: false, isSystem: true, isSupport: true,
  chrome_key: 'Ctrl+X, Shift+Delete',
  browser360_key: 'Ctrl+X, Shift+Delete', maxthon_key: 'Ctrl+X, Shift+Delete',
  tt_key: 'Ctrl+X, Shift+Delete', sogou_key: 'Ctrl+X, Shift+Delete',
  ie6_key: 'Ctrl+X, Shift+Delete', ie7_key: 'Ctrl+X, Shift+Delete',
  ie8_key: 'Ctrl+X, Shift+Delete', opera_key: 'Ctrl+X, Shift+Delete',
  safari_key: 'Ctrl+X, Shift+Delete', firefox_key: 'Ctrl+X, Shift+Delete'
};
key_util.function_table[48] = {
  id: 48, function_name: 'hide_restore_all_windows',
  function_description: 'hide_restore_all_windows',
  category: key_util.category_table.CAT_BOSS_KEY,
  isQuickly: true, isSystem: false, isSupport: true,
  chrome_key: '',
  browser360_key: 'Alt+`', maxthon_key: 'Alt+`',
  tt_key: 'Alt+`', sogou_key: 'Alt+`',
  ie6_key: '', ie7_key: '',
  ie8_key: '', opera_key: '',
  safari_key: '', firefox_key: ''
};
key_util.function_table[49] = {
  id: 49, function_name: 'fill_form',
  function_description: 'fill_form',
  category: key_util.category_table.CAT_FILL_FORM,
  isQuickly: false, isSystem: false, isSupport: true,
  chrome_key: '',
  browser360_key: '', maxthon_key: 'Alt+Q',
  tt_key: 'F9', sogou_key: '',
  ie6_key: '', ie7_key: '',
  ie8_key: '', opera_key: '',
  safari_key: '', firefox_key: ''
  }
key_util.function_table[50] = {
  id: 50, function_name: 'save_form',
  function_description: 'save_form',
  category: key_util.category_table.CAT_FILL_FORM,
  isQuickly: false, isSystem: false, isSupport: true,
  chrome_key: '',
  browser360_key: '', maxthon_key: 'Alt+1',
  tt_key: 'Ctrl+F9', sogou_key: '',
  ie6_key: '', ie7_key: '',
  ie8_key: '', opera_key: '',
  safari_key: '', firefox_key: ''
};
key_util.function_table[51] = {
  id: 51, function_name: 'quick_launch_1',
  function_description: 'quick_launch_1',
  category: key_util.category_table.CAT_QUICK_LAUNCH,
  isQuickly: true, isSystem: false, isSupport: true,
  chrome_key: '',
  browser360_key: 'F1', maxthon_key: 'F1',
  tt_key: '', sogou_key: '',
  ie6_key: '', ie7_key: '',
  ie8_key: '', opera_key: '',
  safari_key: '', firefox_key: ''
};
key_util.function_table[52] = {
  id: 52, function_name: 'quick_launch_2',
  function_description: 'quick_launch_2',
  category: key_util.category_table.CAT_QUICK_LAUNCH,
  isQuickly: true, isSystem: false, isSupport: true,
  chrome_key: '',
  browser360_key: 'F2', maxthon_key: 'F2',
  tt_key: '', sogou_key: '',
  ie6_key: '', ie7_key: '',
  ie8_key: '', opera_key: '',
  safari_key: '', firefox_key: ''
};
key_util.function_table[53] = {
  id: 53, function_name: 'quick_launch_3',
  function_description: 'quick_launch_3',
  category: key_util.category_table.CAT_QUICK_LAUNCH,
  isQuickly: true, isSystem: false, isSupport: true,
  chrome_key: '',
  browser360_key: 'F3', maxthon_key: 'F3',
  tt_key: '', sogou_key: '',
  ie6_key: '', ie7_key: '',
  ie8_key: '', opera_key: '',
  safari_key: '', firefox_key: ''
};
key_util.function_table[54] = {
  id: 54, function_name: 'quick_launch_4',
  function_description: 'quick_launch_4',
  category: key_util.category_table.CAT_QUICK_LAUNCH,
  isQuickly: true, isSystem: false, isSupport: true,
  chrome_key: '',
  browser360_key: 'F4', maxthon_key: 'F4',
  tt_key: '', sogou_key: '',
  ie6_key: '', ie7_key: '',
  ie8_key: '', opera_key: '',
  safari_key: '', firefox_key: ''
};
key_util.function_table[55] = {
  id: 55, function_name: 'quick_launch_5',
  function_description: 'quick_launch_5',
  category: key_util.category_table.CAT_QUICK_LAUNCH,
  isQuickly: true, isSystem: false, isSupport: true,
  chrome_key: '',
  browser360_key: 'F5', maxthon_key: 'F5',
  tt_key: '', sogou_key: '',
  ie6_key: '', ie7_key: '',
  ie8_key: '', opera_key: '',
  safari_key: '', firefox_key: ''
};
key_util.function_table[56] = {
  id: 56, function_name: 'quick_launch_6',
  function_description: 'quick_launch_6',
  category: key_util.category_table.CAT_QUICK_LAUNCH,
  isQuickly: true, isSystem: false, isSupport: true,
  chrome_key: '',
  browser360_key: 'F6', maxthon_key: 'F6',
  tt_key: '', sogou_key: '',
  ie6_key: '', ie7_key: '',
  ie8_key: '', opera_key: '',
  safari_key: '', firefox_key: ''
};
key_util.function_table[57] = {
  id: 57, function_name: 'quick_launch_7',
  function_description: 'quick_launch_7',
  category: key_util.category_table.CAT_QUICK_LAUNCH,
  isQuickly: true, isSystem: false, isSupport: true,
  chrome_key: '',
  browser360_key: 'F7', maxthon_key: 'F7',
  tt_key: '', sogou_key: '',
  ie6_key: '', ie7_key: '',
  ie8_key: '', opera_key: '',
  safari_key: '', firefox_key: ''
};
key_util.function_table[58] = {
  id: 58, function_name: 'quick_launch_8',
  function_description: 'quick_launch_8',
  category: key_util.category_table.CAT_QUICK_LAUNCH,
  isQuickly: true, isSystem: false, isSupport: true,
  chrome_key: '',
  browser360_key: 'F8', maxthon_key: 'F8',
  tt_key: '', sogou_key: '',
  ie6_key: '', ie7_key: '',
  ie8_key: '', opera_key: '',
  safari_key: '', firefox_key: ''
};
key_util.function_table[59] = {
  id: 59, function_name: 'quick_launch_9',
  function_description: 'quick_launch_9',
  category: key_util.category_table.CAT_QUICK_LAUNCH,
  isQuickly: true, isSystem: false, isSupport: true,
  chrome_key: '',
  browser360_key: 'F9', maxthon_key: 'F9',
  tt_key: '', sogou_key: '',
  ie6_key: '', ie7_key: '',
  ie8_key: '', opera_key: '',
  safari_key: '', firefox_key: ''
};
key_util.function_table[60] = {
  id: 60, function_name: 'mute_browser',
  function_description: 'mute_browser',
  category: key_util.category_table.CAT_MUTE,
  isQuickly: false, isSystem: false, isSupport: false,
  chrome_key: '',
  browser360_key: 'Ctrl+Shift+M', maxthon_key: '',
  tt_key: '', sogou_key: 'Alt+W',
  ie6_key: '', ie7_key: '',
  ie8_key: '', opera_key: '',
  safari_key: '', firefox_key: ''
};
key_util.function_table[61] = {
  id: 61, function_name: 'refresh_all_tabs',
  function_description: 'refresh_all_tabs',
  category: key_util.category_table.CAT_WEB_PAGE,
  isQuickly: false, isSystem: false, isSupport: false,
  chrome_key: '',
  browser360_key: '', maxthon_key: 'Shift+F5',
  tt_key: 'Shift+F5', sogou_key: 'Shift+F5',
  ie6_key: '', ie7_key: '',
  ie8_key: '', opera_key: 'Ctrl+F5',
  safari_key: '', firefox_key: ''
};
key_util.function_table[62] = {
  id: 62, function_name: 'hide_current_window',
  function_description: 'hide_current_window',
  category: key_util.category_table.CAT_BOSS_KEY,
  isQuickly: true, isSystem: false, isSupport: true,
  chrome_key: '',
  browser360_key: '', maxthon_key: '',
  tt_key: '', sogou_key: '',
  ie6_key: '', ie7_key: '',
  ie8_key: '', opera_key: '',
  safari_key: '', firefox_key: ''
};
key_util.function_table[63] = {
  id: 63, function_name: 'restore_last_hidden_window',
  function_description: 'restore_last_hidden_window',
  category: key_util.category_table.CAT_BOSS_KEY,
  isQuickly: true, isSystem: false, isSupport: true,
  chrome_key: '',
  browser360_key: '', maxthon_key: '',
  tt_key: '', sogou_key: '',
  ie6_key: '', ie7_key: '',
  ie8_key: '', opera_key: '',
  safari_key: '', firefox_key: ''
};

key_util.extension_support_shortcut_map = [
  {
    id: 48, shortcut: '18+192', type: true, relationId: '',
    operation: 'bossKey', extensionId: ''
  }, {
    id: 49, shortcut: '120', type: false, relationId: '',
    operation: 'fillForm', extensionId: ''
  }, {
    id: 50, shortcut: '121', type: false, relationId: '',
    operation: 'saveForm', extensionId: ''
  }, {
    id: 51, shortcut: '18+49', type: false, relationId: '',
    operation: 'quickLaunch', extensionId: ''
  }, {
    id: 52, shortcut: '18+50', type: false, relationId: '',
    operation: 'quickLaunch', extensionId: ''
  }, {
    id: 53, shortcut: '18+51', type: false, relationId: '',
    operation: 'quickLaunch', extensionId: ''
  }, {
    id: 54, shortcut: '18+52', type: false, relationId: '',
    operation: 'quickLaunch', extensionId: ''
  }, {
    id: 55, shortcut: '18+53', type: false, relationId: '',
    operation: 'quickLaunch', extensionId: ''
  }, {
    id: 56, shortcut: '18+54', type: false, relationId: '',
    operation: 'quickLaunch', extensionId: ''
  }, {
    id: 57, shortcut: '18+55', type: false, relationId: '',
    operation: 'quickLaunch', extensionId: ''
  }, {
    id: 58, shortcut: '18+56', type: false, relationId: '',
    operation: 'quickLaunch', extensionId: ''
  }, {
    id: 59, shortcut: '18+57', type: false, relationId: '',
    operation: 'quickLaunch', extensionId: ''
  }, {
    id: 60, shortcut: '18+87', type: false, relationId: '',
    operation: 'browserMute', extensionId: ''
  }, {
    id: 61, shortcut: '18+116', type: false, relationId: '',
    operation: 'refreshAllTabs', extensionId: ''
  }, {
    id: 62, shortcut: '18+72', type: false, relationId: '',
    operation: 'hideCurrentWindow', extensionId: ''
  }, {
    id: 63, shortcut: '18+82', type: true, relationId: '',
    operation: 'restoreLastHiddenWindow', extensionId: ''
  }
];

key_util.custom_shortcut_id_list = [
    48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63];

key_util.key_code_map = [];
for (var i = 0; i < 222; i++) {
  key_util.key_code_map[i] = { keyCode: '', name: '' };
}

key_util.key_code_map[8] = { keyCode: 8, name: 'Backspace' };
key_util.key_code_map[9] = { keyCode: 9, name: 'Tab' };
key_util.key_code_map[12] = { keyCode: 12, name: 'Clear' };
key_util.key_code_map[13] = { keyCode: 13, name: 'Enter' };
key_util.key_code_map[16] = { keyCode: 16, name: 'Shift' };
key_util.key_code_map[17] = { keyCode: 17, name: 'Ctrl' };
key_util.key_code_map[18] = { keyCode: 18, name: 'Alt' };
key_util.key_code_map[20] = { keyCode: 20, name: 'CapsLock' };
key_util.key_code_map[27] = { keyCode: 27, name: 'Esc' };
key_util.key_code_map[32] = { keyCode: 32, name: 'Spacebar' };
key_util.key_code_map[33] = { keyCode: 33, name: 'PageUp' };
key_util.key_code_map[34] = { keyCode: 34, name: 'PageDown' };
key_util.key_code_map[35] = { keyCode: 35, name: 'End' };
key_util.key_code_map[36] = { keyCode: 36, name: 'Home' };
key_util.key_code_map[37] = { keyCode: 37, name: 'Left' };
key_util.key_code_map[38] = { keyCode: 38, name: 'Up' };
key_util.key_code_map[39] = { keyCode: 39, name: 'Right' };
key_util.key_code_map[40] = { keyCode: 40, name: 'Down' };
key_util.key_code_map[45] = { keyCode: 45, name: 'Insert' };
key_util.key_code_map[46] = { keyCode: 46, name: 'Delete' };
key_util.key_code_map[47] = { keyCode: 47, name: 'Help' };
key_util.key_code_map[48] = { keyCode:48, name:'0' };
key_util.key_code_map[49] = { keyCode:49, name:'1' };
key_util.key_code_map[50] = { keyCode:50, name:'2' };
key_util.key_code_map[51] = { keyCode:51, name:'3' };
key_util.key_code_map[52] = { keyCode:52, name:'4' };
key_util.key_code_map[53] = { keyCode:53, name:'5' };
key_util.key_code_map[54] = { keyCode:54, name:'6' };
key_util.key_code_map[55] = { keyCode:55, name:'7' };
key_util.key_code_map[56] = { keyCode:56, name:'8' };
key_util.key_code_map[57] = { keyCode:57, name:'9' };
key_util.key_code_map[65] = { keyCode:65, name:'A' };
key_util.key_code_map[66] = { keyCode:66, name:'B' };
key_util.key_code_map[67] = { keyCode:67, name:'C' };
key_util.key_code_map[68] = { keyCode:68, name:'D' };
key_util.key_code_map[69] = { keyCode:69, name:'E' };
key_util.key_code_map[70] = { keyCode:70, name:'F' };
key_util.key_code_map[71] = { keyCode:71, name:'G' };
key_util.key_code_map[72] = { keyCode:72, name:'H' };
key_util.key_code_map[73] = { keyCode:73, name:'I' };
key_util.key_code_map[74] = { keyCode:74, name:'J' };
key_util.key_code_map[75] = { keyCode:75, name:'K' };
key_util.key_code_map[76] = { keyCode:76, name:'L' };
key_util.key_code_map[77] = { keyCode:77, name:'M' };
key_util.key_code_map[78] = { keyCode:78, name:'N' };
key_util.key_code_map[79] = { keyCode:79, name:'O' };
key_util.key_code_map[80] = { keyCode:80, name:'P' };
key_util.key_code_map[81] = { keyCode:81, name:'Q' };
key_util.key_code_map[82] = { keyCode:82, name:'R' };
key_util.key_code_map[83] = { keyCode:83, name:'S' };
key_util.key_code_map[84] = { keyCode:84, name:'T' };
key_util.key_code_map[85] = { keyCode:85, name:'U' };
key_util.key_code_map[86] = { keyCode:86, name:'V' };
key_util.key_code_map[87] = { keyCode:87, name:'W' };
key_util.key_code_map[88] = { keyCode:88, name:'X' };
key_util.key_code_map[89] = { keyCode:89, name:'Y' };
key_util.key_code_map[90] = { keyCode:90, name:'Z' };
key_util.key_code_map[106] = { keyCode: 106, name: '*' };
key_util.key_code_map[107] = { keyCode: 107, name: '+' };
key_util.key_code_map[108] = { keyCode: 108, name: 'Enter' };
key_util.key_code_map[109] = { keyCode: 109, name: '-' };
key_util.key_code_map[110] = { keyCode: 110, name: '.' };
key_util.key_code_map[111] = { keyCode: 111, name: '/' };
key_util.key_code_map[112] = { keyCode:112, name:'F1' };
key_util.key_code_map[113] = { keyCode:113, name:'F2' };
key_util.key_code_map[114] = { keyCode:114, name:'F3' };
key_util.key_code_map[115] = { keyCode:115, name:'F4' };
key_util.key_code_map[116] = { keyCode:116, name:'F5' };
key_util.key_code_map[117] = { keyCode:117, name:'F6' };
key_util.key_code_map[118] = { keyCode:118, name:'F7' };
key_util.key_code_map[119] = { keyCode:119, name:'F8' };
key_util.key_code_map[120] = { keyCode:120, name:'F9' };
key_util.key_code_map[121] = { keyCode:121, name:'F10' };
key_util.key_code_map[122] = { keyCode:122, name:'F11' };
key_util.key_code_map[123] = { keyCode:123, name:'F12' };
key_util.key_code_map[186] = { keyCode: 186, name: ';' };
key_util.key_code_map[187] = { keyCode: 187, name: '=' };
key_util.key_code_map[188] = { keyCode: 188, name: ',' };
key_util.key_code_map[189] = { keyCode: 189, name: '-' };
key_util.key_code_map[190] = { keyCode: 190, name: '.' };
key_util.key_code_map[191] = { keyCode: 191, name: '/' };
key_util.key_code_map[192] = { keyCode: 192, name: '`' };
key_util.key_code_map[219] = { keyCode: 219, name: '[' };
key_util.key_code_map[220] = { keyCode: 220, name: '\\' };
key_util.key_code_map[221] = { keyCode: 221, name: ']' };
key_util.key_code_map[222] = { keyCode: 222, name: '\'' };

key_util.keyCodeToShowName = function(keyCode) {
  var keyCodeList = '';
  if (keyCode) {
    keyCodeList = keyCode.split('+');
    for (var i = 0; i < keyCodeList.length; i++) {
      if (keyCodeList[i]) {
        keyCodeList[i] = key_util.key_code_map[keyCodeList[i]].name;
      }
    }
    keyCodeList = keyCodeList.join('+');
  }
  return keyCodeList;
}

key_util.getVirtualKey = function(shortcut) {
  var returnKey = '';
  if (shortcut) {
    var virtualKey = shortcut.split('+');
    for (var i = 0; i < virtualKey.length; i++) {
      for (var m = 0; m < key_util.key_code_map.length; m++) {
        if (virtualKey[i] == key_util.key_code_map[m].name) {
          virtualKey[i] = key_util.key_code_map[m].keyCode;
          break;
        }
      }
    }
    returnKey = virtualKey.join('+');
  }
  return returnKey;
}


key_util.getObject = function(array, name, value) {
  for (var i = 0; i < array.length; i++) {
    var object = array[i];
    if (object[name] && object[name] == value) {
      return object;
    }
  }
}

key_util.getAllChromeShortcut = function() {
  var chromeShortcutsList = [];
  for (var i = 1; i < key_util.function_table.length; i++) {
    if (key_util.function_table[i].chrome_key) {
      chromeShortcutsList.push(key_util.function_table[i].chrome_key);
    }
  }
  return chromeShortcutsList.join(', ').split(', ');
}

key_util.getCustomShortcutItemById = function(customShortcutList, id) {
  var shortcutItem = '';
  for (var i = 0; i < customShortcutList.length; i++) {
    if (customShortcutList[i].id == id) {
      shortcutItem = customShortcutList[i];
      break;
    }
  }
  return shortcutItem;
}

key_util.chrome_shortcuts = key_util.getAllChromeShortcut();


