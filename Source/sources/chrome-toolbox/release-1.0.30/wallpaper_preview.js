var bg = chrome.extension.getBackgroundPage();
var preview = {
  orgImage: '',
  compressiveImage: '',
  getImageData: function() {
    preview.orgImage = bg.wallpaper.orgImage;
    preview.compressiveImage = bg.wallpaper.compressiveImage;
  },

  getPreviewAreaSize: function() {
    var zoom = 3;
    var previewWidth = Math.round(window.screen.width / zoom);
    var previewHeight = Math.round(window.screen.height / zoom);
    return {previewWidth: previewWidth, previewHeight: previewHeight};
  },

  setTileMode: function(previewArea, image) {
    if (document.getElementById('desktoppreviw')) {
      var img = document.getElementById('desktoppreviw');
      previewArea.removeChild(img);
    }
    previewArea.style.backgroundImage = 'url("' + image.data + '")';
  },

  setCenterMode: function(previewArea, image) {
    var img;
    if (document.getElementById('desktoppreviw')) {
      img = document.getElementById('desktoppreviw');
      previewArea.removeChild(img);
    }
    previewArea.style.backgroundImage = '';
    var previewAreaSize = preview.getPreviewAreaSize();
    var imgWidth = image.width;
    var imgHeight = image.height;
    img = document.createElement('IMG');
    img.style.marginLeft = (previewAreaSize.previewWidth - image.width) / 2 + 'px';
    img.style.marginTop = (previewAreaSize.previewHeight - image.height) / 2 + 'px';
    img.id = 'desktoppreviw';
    img.src = image.data;
    previewArea.appendChild(img);
  },

  setStretchMode: function(previewArea, image) {
    var previewAreaSize = preview.getPreviewAreaSize();
    var img;
    if (document.getElementById('desktoppreviw')) {
      img = document.getElementById('desktoppreviw');
      previewArea.removeChild(img);
    }
    previewArea.style.backgroundImage = '';
    img = document.createElement('IMG');
    img.id = 'desktoppreviw';
    img.src = image.data;
    img.width = previewAreaSize.previewWidth;
    img.height = previewAreaSize.previewHeight;
    previewArea.appendChild(img);
  },

  init: function() {
    i18nReplace('tileText', 'tile_text');
    i18nReplace('centerText', 'center_text');
    i18nReplace('stretchText', 'stretch_text');
    i18nReplace('apply', 'apply');
    i18nReplace('restore', 'restore');
    i18nReplace('close', 'close');
    i18nReplace('position', 'position');
    document.title = chrome.i18n.getMessage('set_wallpaper');
    preview.getImageData();
    var previewArea = document.getElementById('previewArea');
    var size = preview.getPreviewAreaSize();
    preview.setTileMode(previewArea, preview.compressiveImage);
    previewArea.style.width = size.previewWidth + 'px';
    previewArea.style.height =
        previewArea.style.lineHeight = size.previewHeight + 'px';
    document.getElementById('apply').addEventListener('click',
        preview.apply, false);
    document.getElementById('restore').addEventListener('click',
        preview.restore, false);
    document.getElementById('close').addEventListener('click',
        preview.close, false);
    document.addEventListener('change', function(){
      var center = document.getElementById('center');
      var tile = document.getElementById('tile');
      var stretch = document.getElementById('stretch');
      if (center.checked) {
        preview.setCenterMode(previewArea, preview.compressiveImage);
      } else if (tile.checked){
        preview.setTileMode(previewArea, preview.compressiveImage);
      } else if (stretch.checked) {
        preview.setStretchMode(previewArea, preview.compressiveImage);
      }
    }, false);
  },

  apply: function() {
    var mode;
    if (document.getElementById('tile').checked) {
      mode = document.getElementById('tile').value;
    } else if (document.getElementById('center').checked) {
      mode = document.getElementById('center').value;
    } else if (document.getElementById('stretch').checked) {
      mode = document.getElementById('stretch').value;
    }
    bg.plugin.applyWallpaper(preview.orgImage.data, mode);
  },

  restore: function() {
    bg.plugin.restoreWallpaper();
  },

  close: function() {
    window.close();
  }


}
function i18nReplace(id, messageName) {
  document.getElementById(id).innerText = chrome.i18n.getMessage(messageName);
}
preview.init();

