function $(id) {
  var element = document.getElementById(id);
  if (element) {
    return element;
  } else {
    //throw new Error('$: not found:' + id);
    return false;
  }
}

function i18nReplace(id, messageName) {
  $(id).innerText = chrome.i18n.getMessage(messageName);
}
var fillForm = new FillForm();
var shortcut = new Shortcut();
function setMessage() {
  var i18n_map = [
    {id: 'optionTitle', message: 'option_title'},
    {id: 'description', message: 'description'},
    {id: 'mGeneral', message: 'tab_general' },
    {id: 'mFillForm', message: 'tab_fill_form' },
    {id: 'mQuicklyVisit', message: 'tab_quick_launch'},
    {id: 'mShortcut', message: 'tab_shortcut'},
    {id: 'mRecommended', message: 'tab_recommended'},
    {id: 'title_floatingBar', message: 'title_floating_bar'},
    {id: 'title_tab', message: 'title_tab'},
    {id: 'title_contextMenu', message: 'title_context_menu'},
    {id: 'item_imageBar', message: 'item_image_bar'},
    {id: 'item_videoBar', message: 'item_video_bar'},
    {id: 'item_closeLastTab', message: 'item_close_last_tab'},
    {id: 'item_openInNewTab', message: 'item_open_in_new_tab'},
    {id: 'item_openInBefore', message: 'item_open_in_before'},
    {id: 'item_openInBehind', message: 'item_open_in_behind'},
    {id: 'item_dbClickCloseTab', message: 'item_double_click_close_tab'},
    {id: 'item_closeChromePrompt', message: 'item_close_chrome_prompt'},
    {id: 'item_mouseWheelSwitchTab', message: 'item_mouse_wheel_switch_tab'},
    {id: 'item_enableContextMenu', message: 'item_enable_context_menu'},
    {id: 'item_pressEnterOpenNewTab', message: 'item_press_enter_open_new_tab'},    
    {id: 'fillForm_title', message: 'fill_form_title'},
    {id: 'fillForm_address', message: 'fill_form_url'},
    {id: 'fillForm_date', message: 'fill_form_date'},
    {id: 'fillFrom_delAll', message: 'fill_from_delete_all'},
    {id: 'shortcut_compare', message: 'shortcut_compare'},
    {id: 'quick_launch_selected_folder', message: 'quick_launch_select_folder'},
    {
      id: 'quick_launch_manage_bookmark', 
      message: 'quick_launch_manage_bookmark'
    },
    {id: 'quick_launch_close', message: 'quick_launch_close'},
    {id: 'bookmark_tip', message: 'bookmark_tip'},
    {id: 'shortcut_tip', message: 'tab_shortcut_description'},
    {id: 'fillForm_tip', message: 'tab_fill_form_description'},
    {id: 'gotoShortcutTab', message: 'bookmark_tip2'},
    {id: 'more', message: 'more'},
    {id: 'more2', message: 'more'},
    {id: 'recommended_fromGoogle', message: 'recommended_from_google'},
    {id: 'recommended_fromThird', message: 'recommended_from_third_party'},
    {id: 'disclaimer', message: 'disclaimer'},
    {id: 'termsOfService', message: 'terms_of_service'},
    {id: 'privacyPolicy', message: 'privacy_policy'},
    {id: 'form_close', message: 'form_close'},
  ];
  document.title = chrome.i18n.getMessage('option_title');
  for (var i = 0, l = i18n_map.length; i < l; i++) {
    var id = i18n_map[i].id;
    var name = i18n_map[i].message;
    i18nReplace(id, name);
  }
}

function Option() {
  var self = this;

  //checkbox element
  this.imageBar = $('imageBar');
  this.videoBar = $('videoBar');
  this.closeLastTab = $('closeLastTab');
  this.openInNewTab = $('openInNewTab');
  this.openInBefore = $('openInBefore');
  this.openInBehind = $('openInBehind');
  this.dbclickCloseTab = $('dbclickCloseTab');
  this.closeChromePrompt = $('closeChromePrompt');
  this.mouseWheelSwitchTab = $('mouseWheelSwitchTab');
  this.enableContextMenu = $('enableContextMenu');
  this.pressEnterOpenNewTab = $('pressEnterOpenNewTab');
  this.isCompare = $('isCompare');

  //div element
  this.nav_general = $('mGeneral');
  this.nav_fillForm = $('mFillForm');
  this.nav_quicklyVisit = $('mQuicklyVisit');
  this.nav_shortcut = $('mShortcut');
  this.nav_recommended = $('mRecommended');

  this.tab_general = $('generalTab');
  this.tab_fillForm = $('fillFormTab');
  this.tab_quicklyVisit = $('quicklyVisitTab');
  this.tab_shortcut = $('shortcutTab');
  this.tab_recommended = $('recommendedTab');

  //form tab element
  this.form_deleteAll = $('form_deleteAll');
  this.form_close = $('form_close');
  this.form_content = $('formContent');

  //a element
  this.gotoShortcutTab = $('gotoShortcutTab');
  this.termsOfService = $('termsOfService');
  this.privacyPolicy = $('privacyPolicy');
  this.termsOfService.href = chrome.i18n.getMessage('terms_of_service_link');
  this.privacyPolicy.href = chrome.i18n.getMessage('privacy_policy_link');

  //Recommended tab element
  this.googleExtensionsRecommended = $('googleExtensionsRecommended');
  this.thirdPartyExtensionsRecommended = $('thirdPartyExtensionsRecommended');

  this.table_shortcut = $('shortcutTable');

  this.setNavigationBarStatus(this.nav_general);
  this.nav_general.addEventListener('click',
      this.setNavigationBarStatus, false);
  this.nav_fillForm.addEventListener('click',
      this.setNavigationBarStatus, false);
  this.nav_quicklyVisit.addEventListener('click',
      this.setNavigationBarStatus, false);
  this.nav_shortcut.addEventListener('click',
      this.setNavigationBarStatus, false);
  this.nav_recommended.addEventListener('click',
      this.setNavigationBarStatus, false);

  if (isWindowsPlatform())
    createQuickLaunchTab();
  
  fillForm.showAllFormDate();
  this.form_deleteAll.addEventListener('click', function() {
    fillForm.deleteAllData();
    fillForm.showAllFormDate();
  }, false);
  this.form_close.addEventListener('click', function() {
    this.form_content.style.display = 'none';
  }, false);
  this.setGeneralTabOption();

  if (isWindowsPlatform()) {
    var categorySelect = shortcut.createSelect(key_util.category_table);
    var browserSelect = shortcut.createSelect(key_util.browser);

    this.isCompare.addEventListener('change', function() {
      self.table_shortcut.innerHTML = '';
      self.table_shortcut.appendChild(shortcut.showTable(
          categorySelect, browserSelect, self.isCompare.checked));
    }, false);
    categorySelect.addEventListener('change', function() {
      self.table_shortcut.innerHTML = '';
      self.table_shortcut.appendChild(shortcut.showTable(
          categorySelect, browserSelect, self.isCompare.checked));
    }, false);
    browserSelect.addEventListener('change', function() {
      self.table_shortcut.innerHTML = '';
      self.table_shortcut.appendChild(shortcut.showTable(
          categorySelect, browserSelect, self.isCompare.checked));
    }, false);
    this.table_shortcut.appendChild(shortcut.showTable(
        categorySelect, browserSelect, self.isCompare.checked));

    this.gotoShortcutTab.addEventListener('click', function() {
      categorySelect.value = key_util.category_table.CAT_QUICK_LAUNCH;
      self.table_shortcut.innerHTML = '';
      self.table_shortcut.appendChild(shortcut.showTable(
          categorySelect, browserSelect, self.isCompare.checked));
      self.setNavigationBarStatus(self.nav_shortcut);
    }, false)
  }

  createRecommendedContext(this.googleExtensionsRecommended,
                                  this.thirdPartyExtensionsRecommended);
  setMessage();
  setWindowOnlyElement();
  var url = location.href;
  if (url.indexOf('#') > -1) {
    var parameter = url.substr(url.indexOf('#') + 1, url.length);
    if (parameter == 'bossKey') {
      categorySelect.value = key_util.category_table.CAT_BOSS_KEY;
      this.table_shortcut.innerHTML = '';
      this.table_shortcut.appendChild(shortcut.showTable(categorySelect,
          browserSelect, this.isCompare.checked));
      self.setNavigationBarStatus(this.nav_shortcut);
    }
  }
}

Option.prototype.setNavigationBarStatus = function(element) {
  var this_obj = this;
  if (arguments.length == 1 && arguments[0] != event) {
    this_obj = element;
  }
  var navigationBarMap = [
      {menu: 'mGeneral', tab: 'generalTab', isWindowsOnly: false},
      {menu: 'mFillForm', tab: 'fillFormTab', isWindowsOnly: false},
      {menu: 'mQuicklyVisit', tab: 'quicklyVisitTab', isWindowsOnly: true},
      {menu: 'mShortcut', tab: 'shortcutTab', isWindowsOnly: true},
      {menu: 'mRecommended', tab: 'recommendedTab', isWindowsOnly: false}];
  for (var i = 0, l = navigationBarMap.length; i < l; i++) {
    var navMenu = $(navigationBarMap[i].menu);
    var tab = $(navigationBarMap[i].tab);
    if (navMenu == this_obj) {
      navMenu.className = 'choosed';
      tab.style.display = 'block';
    } else {
      navMenu.className = '';
      tab.style.display = 'none';
    }
  }
};

Option.prototype.setGeneralTabOption = function() {
  var bg = chrome.extension.getBackgroundPage();
  this.imageBar.checked = eval(localStorage['imageBar']);
  this.videoBar.checked = eval(localStorage['videoBar']);
  this.closeLastTab.checked = eval(localStorage['closeLastTab']);
  this.openInNewTab.checked = eval(localStorage['openInNewTab']);
  this.openInBefore.checked = eval(localStorage['openInBefore']);
  this.openInBehind.checked = eval(localStorage['openInBehind']);
  this.dbclickCloseTab.checked = eval(localStorage['dbclickCloseTab']);
  this.closeChromePrompt.checked = eval(localStorage['closeChromePrompt']);
  this.mouseWheelSwitchTab.checked = 
      eval(localStorage['mouseWheelSwitchTab']);
  this.enableContextMenu.checked = eval(localStorage['enableContextMenu']);
  this.pressEnterOpenNewTab.checked = 
      eval(localStorage['pressEnterOpenNewTab']);
  disabledRadioOrNOt();
  this.imageBar.addEventListener('change', function() {
    localStorage['imageBar'] = $('imageBar').checked;
    showSavingSucceedTip();
  });
  this.videoBar.addEventListener('change', function() {
    localStorage['videoBar'] = $('videoBar').checked;
    showSavingSucceedTip();
  });
  this.closeLastTab.addEventListener('change', function() {
    localStorage['closeLastTab'] = $('closeLastTab').checked;
    bg.setCloseLastOneTabStatus();
    showSavingSucceedTip();
  });
  this.openInNewTab.addEventListener('change', function() {
    disabledRadioOrNOt();
    localStorage['openInNewTab'] = $('openInNewTab').checked;
    showSavingSucceedTip();
  }, false);
  this.openInBefore.addEventListener('change', function() {
    changeCheckedRadio('openInBehind', 'openInBefore');
  });
  this.openInBehind.addEventListener('change', function() {
    changeCheckedRadio('openInBefore', 'openInBehind');
  });
  this.dbclickCloseTab.addEventListener('change', function() {
    localStorage['dbclickCloseTab'] = $('dbclickCloseTab').checked;
    bg.dbClickCloseTab();
    showSavingSucceedTip();
  }, false);
  this.closeChromePrompt.addEventListener('change', function() {
    localStorage['closeChromePrompt'] = $('closeChromePrompt').checked;
    bg.plugin.closeChromePrompt(eval(localStorage['closeChromePrompt']));
    showSavingSucceedTip();
  }, false);
  this.mouseWheelSwitchTab.addEventListener('change', function() {
    localStorage['mouseWheelSwitchTab'] = $('mouseWheelSwitchTab').checked;
    bg.mouseWheelSwitchTab();
    showSavingSucceedTip();
  }, false);
  this.enableContextMenu.addEventListener('change', function() {
    localStorage['enableContextMenu'] = $('enableContextMenu').checked;
    bg.enableContextMenu();
    showSavingSucceedTip();
  }, false);
  this.pressEnterOpenNewTab.addEventListener('change', function() {
    localStorage['pressEnterOpenNewTab'] = $('pressEnterOpenNewTab').checked;
    bg.pressEnterOpenNewTab();
    showSavingSucceedTip();
  }, false);
}

function disabledRadioOrNOt() {
  var openInNewTabChecked = $('openInNewTab').checked;
  localStorage['openInNewTab'] = openInNewTabChecked;
  if (openInNewTabChecked) {
    $('openInBefore').removeAttribute('disabled');
    $('openInBehind').removeAttribute('disabled');
  } else {
    $('openInBefore').setAttribute('disabled', 'disabled');
    $('openInBehind').setAttribute('disabled', 'disabled');
  }
}

function changeCheckedRadio(changeId, checkedId) {
  $(changeId).checked = false;
  localStorage[changeId] = false;
  localStorage[checkedId] = $(checkedId).checked;
  showSavingSucceedTip();
}

function showSavingSucceedTip() {
  var div = document.createElement('DIV');
  div.className = 'tip_succeed';
  div.innerText = chrome.i18n.getMessage('tip_succeed');
  document.body.appendChild(div);
  div.style.left = (document.body.clientWidth - div.clientWidth) / 2 + 'px';
  window.setTimeout(function() {
    document.body.removeChild(div);
  }, 2000);
}

function showSavingFailedTip(msg) {
  var div = document.createElement('DIV');
  div.className = 'tip_failed';
  div.innerText = chrome.i18n.getMessage(msg);
  document.body.appendChild(div);
  div.style.left = (document.body.clientWidth - div.clientWidth) / 2 + 'px';
  window.setTimeout(function() {
    document.body.removeChild(div);
  }, 5000);
}

function setWindowOnlyElement() {
  if (!isWindowsPlatform()) {
    var elements = document.getElementsByName('isWindowsOnly');
    for (var i = 0, l = elements.length; i < l; i++) {
      elements[i].style.display = 'none';
    }
    i18nReplace('item_imageBar', 'item_image_bar_not_windows');
    i18nReplace('description', 'description_linux_and_mac');
  }
}

function redirectTabByUrlParameter() {
  var url = document.href;
  if (url.indexOf('#') > -1) {
    var parameter = url.substr(url.indexOf('#'), url.length);
    if (parameter == 'bosskey') {
    }
  }
}

function createRecommendedContext(googleExtensionsRecommended,
                                  thirdPartyExtensionsRecommended) {
  var createTable = function(list, parent) {
    var table = document.createElement('TABLE');
    table.className = 'recommendedTable';
    for(var i = 0; i < list.length; i++) {
      if (isWindowsPlatform() || !list[i].isWindowsOnly) {
        var tr = document.createElement('TR');
        var td1 = document.createElement('TD');
        td1.className = 'description';
        td1.innerText = chrome.i18n.getMessage(list[i].description);
        tr.appendChild(td1);
        var td2 = document.createElement('TD');
        td2.className = 'image';
        td2.innerHTML = '<img src="' +
            chrome.extension.getURL(list[i].icon) + '" alt="">';
        tr.appendChild(td2);
        var td3 = document.createElement('TD');
        td3.innerHTML = '<a href="' + list[i].href + '" target="_blank">' +
            chrome.i18n.getMessage(list[i].name) + '</a>';
        tr.appendChild(td3);
        table.appendChild(tr);
      }
    }
    parent.appendChild(table);
  }
  var googleExtensionsList = [{
    name: 'recommended_screen_capture',
    description: 'recommended_screen_capture_desc',
    icon: 'images/icon_capture_32.png',
    isWindowsOnly: false,
    href: 'https://chrome.google.com/extensions/detail/' + 
          'cpngackimfmofbokmjmljamhdncknpmg' 
  }, {
    name: 'recommended_download_helper',
    description: 'recommended_download_helper_desc',
    icon: 'images/icon_download_32.png',
    isWindowsOnly: true,
    href: 'https://chrome.google.com/extensions/detail/' + 
          'mfjkgbjaikamkkojmakjclmkianficch' 
  }, {
    name: 'recommended_google_translate',
    description: 'recommended_google_translate_desc',
    icon: 'images/icon_translate_32.gif',
    isWindowsOnly: false,
    href: 'https://chrome.google.com/extensions/detail/' + 
          'aapbdbdomjkkjkaonfhkkikfgjllcleb' 
  }];
  var thirdPartyExtensionsList = [{
    name: 'recommended_proxy_switch',
    description: 'recommended_proxy_switch_desc',
    icon: 'images/icon_proxy_32.png',
    isWindowsOnly: false,
    href: 'https://chrome.google.com/extensions/detail/' + 
          'caehdcpeofiiigpdhbabniblemipncjj' 
  }, {
    name: 'recommended_drag_and_go',
    description: 'recommended_drag_and_go_desc',
    icon: 'images/icon_dragandgo_32.png',
    isWindowsOnly: false,
    href: 'https://chrome.google.com/extensions/detail/' + 
          'jaikcnhlohebodlpkmjepipngegjbfpg' 
  }, {
    name: 'recommended_smooth_gestures',
    description: 'recommended_smooth_gestures_desc',
    icon: 'images/icon_gestures_32.png',
    isWindowsOnly: false,
    href: 'https://chrome.google.com/extensions/detail/' + 
          'lfkgmnnajiljnolcgolmmgnecgldgeld' 
  }, {
    name: 'recommended_tab_menu',
    description: 'recommended_tab_menu_desc',
    icon: 'images/icon_tab_menu_35.png',
    isWindowsOnly: false,
    href: 'https://chrome.google.com/extensions/detail/' + 
          'galfofdpepkcahkfobimileafiobdplb' 
  }];
  createTable(googleExtensionsList, googleExtensionsRecommended);
  createTable(thirdPartyExtensionsList, thirdPartyExtensionsRecommended);
}

function init() {
  new Option();
}
