  var selectedBookmarkNodeId = 0;
  var quickLaunchShortcutId = 0;
  function openMyBookmarkManager(id) {
    createBookmarkFolder(id);
    quickLaunchShortcutId = id;
    $('bookmarkList').innerHTML = '';
  }

  function createBookmarkFolder(selectedId) {
    chrome.bookmarks.getTree(function(bookmarkTreeNode) {
      $('bookmarkTree').innerHTML = '';
      var ul = document.createElement('UL');
      ul.id = 'bookmark_folder_menu';
      var getBookmarkFolder = function(parent, bookmarkTreeNode) {
        for (var i = 0; i < bookmarkTreeNode.length; i++) {
          var li = document.createElement('li');
          var node = bookmarkTreeNode[i];
          if (node.children) {
            li.id = 'bookmarkNode_' + node.id;
            var url = chrome.extension.getURL('images/folder_close.png');
            if (node.id != 0) {
              li.innerHTML = '<img src ="' + url + '" alt="">' +  node.title;
              (function(id) {
                li.onclick = function() {
                  selectBookMarks(id)
                }
              })(node.id);
              parent.appendChild(li);
            }
            getBookmarkFolder(parent, node.children);
          }
        }
      };
      getBookmarkFolder(ul, bookmarkTreeNode);
      selectedFolderById(selectedId);
      $('bookmarkTree').appendChild(ul);
      $('bookmarkBox').style.display = 'block';
      var left = (document.body.clientWidth - $('bookmarkBox').clientWidth) / 2;
      $('bookmarkBox').style.left = left + 'px';
    });
  }
  
  function selectBookMarks(id) {
    createSelectedBookmarkFolderLinks(id);
    setSelectedFolderClass(id);
  }

  function createQuickLaunchTab() {
    var quickLaunchIds = [51, 52, 53, 54, 55, 56, 57, 58, 59];
    var table = document.createElement('TABLE');
    for (var i = 0; i < quickLaunchIds.length; i++) {
      shortcut.selectById(quickLaunchIds[i], function(tx, results) {
        if (results.rows.length > 0) {
          var id = results.rows.item(0).id;
          var virtualKey = results.rows.item(0).shortcut;
          var tr = document.createElement('TR');
          var td1 = document.createElement('TD');
          td1.innerText =
              key_util.keyCodeToShowName(virtualKey);
          tr.appendChild(td1);
          var td2 = document.createElement('TD');
          var input = document.createElement('DIV');
          input.className = 'input';
          //input.id = 'input_' + results.rows.item(0).id;
          var span = document.createElement('SPAN');
          span.id = 'input_' + results.rows.item(0).id;
          var resetButton = document.createElement('IMG');
          resetButton.src = chrome.extension.getURL('images/del.png');
          resetButton.className = 'resetButton';
          input.appendChild(span);
          input.appendChild(resetButton);
          td2.appendChild(input);
          tr.appendChild(td2);
          var td3 = document.createElement('TD');
          var img = document.createElement("IMG");
          img.src = chrome.extension.getURL('images/folder_open.png');
          (function(input, span, img, resetButton, id, selectedNodeId) {
            var tip = chrome.i18n.getMessage('bookmark_tip3');
            input.onclick = function() {
              if (!span.innerText) {
                span.innerText = tip;
                span.style.color = '#d9d9d9';
              }
            };
            input.onmousemove = function() {
              if (span.innerText && span.innerText != tip) {
                resetButton.style.display = 'block';
              }
            };
            input.onmouseout = function() {
              resetButton.style.display = 'none';
            };
            resetButton.onclick = function() {
              resetQuickLunch(id, span);
              event.stopPropagation();
            }
            setSelectedBookmarkFolderName(span, selectedNodeId);
            img.onclick = function() {
              openMyBookmarkManager(id);
            };
          })(input, span, img, resetButton, results.rows.item(0).id,
              results.rows.item(0).relationId);
          td3.appendChild(img);
          tr.appendChild(td3);
          table.appendChild(tr);
        }
      });
    }
    $('openBookmark').appendChild(table);
  }

  function openBookmarkFolderLinks(nodeId) {
    chrome.bookmarks.getChildren(nodeId, function(children) {
      for (var i = 0; i < children.length; i++) {
        if (children[i].url) {
          chrome.tabs.create({url: children[i].url});
        } else {
          openBookmarkFolderLinks(children[i].id.toString());
        }
      }
    });
  }

  function createSelectedBookmarkFolderLinks(node) {
    $('bookmarkList').innerHTML = '';
    var ul = document.createElement('UL');
    var traversalAllNode = function(nodeId) {
      chrome.bookmarks.getChildren(nodeId, function(children) {
        for (var i = 0; i < children.length; i++) {
          if (children[i].url) {
            var li = document.createElement('li');
            li.innerHTML = '<a href="' + children[i].url +
                '" target="_blank" ><img src="chrome://favicon/' + children[i].url +
                '" width="16" height="16" alt=""/>' +
                children[i].title + '</a>';
            ul.appendChild(li);
          } else {
            traversalAllNode(children[i].id);
          }
        }
      });
    }
    traversalAllNode(node);
    $('bookmarkList').appendChild(ul);
  }

  function closeBox(id) {
    $(id).style.display = 'none';
  }

  function openBookmarkTab() {
    $('bookmarkBox').style.display = 'none';
    chrome.tabs.create({url:'chrome://bookmarks/', selected:true});
  }

  function setSelectedFolderClass(id) {
    if (id) {
      var children = $('bookmark_folder_menu').childNodes;
      for (var i = 0; i < children.length; i++) {
        children[i].className = '';
      }
      $('bookmarkNode_' + id).className = 'selected';
      selectedBookmarkNodeId = id;
    }

  }

  function setSelectedBookmarkFolderName(element, nodeId) {
    if (nodeId) {
      chrome.bookmarks.get(nodeId.toString(), function(bookmarkTreeNode) {
        if (bookmarkTreeNode.length > 0) {
          element.innerText = bookmarkTreeNode[0].title;
          element.style.color = '#333333';
        }
      });
    }
  }

  function setSelectedBookmarkFolder() {
    if (selectedBookmarkNodeId && quickLaunchShortcutId) {
      var inputId = 'input_' + quickLaunchShortcutId;
      setSelectedBookmarkFolderName($(inputId) ,selectedBookmarkNodeId);
      shortcut.updateRelationId(selectedBookmarkNodeId, quickLaunchShortcutId);
      selectedBookmarkNodeId = 0;
      quickLaunchShortcutId = 0;
      showSavingSucceedTip();
      $('bookmarkBox').style.display = 'none';
    } else {
      showSavingFailedTip('tip_failed2');
    }
  }

  function selectedFolderById(id) {
    shortcut.selectById(id, function(tx, results) {
      if (results.rows.length > 0 && results.rows.item(0).relationId) {
        var relationId = results.rows.item(0).relationId;
        $('bookmarkNode_' + relationId).className = 'selected'; 
        createSelectedBookmarkFolderLinks(relationId);
      } else {
        selectBookMarks('1')
      }
    });
  }

  function resetQuickLunch(shortcutId, input) {
    shortcut.updateRelationId(null, shortcutId);
    input.innerText = '';
    showSavingSucceedTip();
  }



