var dragAndDrop = {
  isClickEvent: true,
  startY: 0,
  isMouseDown: false,
  isMouseMove: false,
  curElement: null,
  makeElementSortable: function(element, shortcut) {
    element.style.position = 'relative';
    element.addEventListener('mousedown', this.dragInit, true);
    element.addEventListener('mousemove', this.drag, true);
    element.addEventListener('mouseup', this.dragEnd, true);
    element.addEventListener('click', function() {
      dragAndDrop.onClick(shortcut);
    }, false);

  },

  getStyle: function(element, property) {
    if (element.style[property]) {
      return element.style[property];
    }
    return false;
  },

  leftTopOffset: function(element) {
    var offsetLeft = element.offsetLeft;
    var offsetTop = element.offsetTop;
    var parent = element.offsetParent;
    while(parent != document.body) {
      offsetLeft += parent.offsetLeft;
      offsetTop += parent.offsetTop;
      parent = parent.offsetParent;
    }
    return {left: offsetLeft, top: offsetTop};
  },

  rightBottomOffset: function(element) {
    var leftTopOffset = this.leftTopOffset(element);
    var offsetRight = leftTopOffset.left + element.offsetWidth;
    var offsetBottom = leftTopOffset.top + element.offsetHeight;
    return {offsetRight: offsetRight, offsetBottom: offsetBottom};
  },

  nextItem : function(element) {
    do {
      element = element.nextSibling;
    } while(element && element.nodeType != 1)
    return element;

  },

  previousItem : function(element) {
    do {
      element = element.previousSibling
    }
    while(element && element.nodeType != 1)
    return element;
  },

  moveBefore: function(curElement, moveTo) {
    var parent = curElement.parentNode;
    parent.removeChild(curElement);
    parent.insertBefore(curElement, moveTo)
  },

  dragInit: function() {
    dragAndDrop.isMouseDown = true;
    dragAndDrop.startY = event.clientY;
    dragAndDrop.curElement = this;
    this.style.zIndex = 100;
    this.style.cursor = 'move';
    event.preventDefault();
  },

  drag: function(event) {
    var element = event.target;
    if (!dragAndDrop.isMouseDown || dragAndDrop.curElement != this) {
      return;
    }
    dragAndDrop.isMouseMove = true;
    var startY = dragAndDrop.startY;

    element.style.top = event.clientY - startY + 'px';
    var nextItem = dragAndDrop.nextItem(dragAndDrop.curElement);

    if (nextItem != null) {
      var topMargin = dragAndDrop.leftTopOffset(nextItem).top;
      if (event.clientY >= topMargin) {
        dragAndDrop.moveBefore(nextItem, element);
        element.style.top = event.clientY - startY - 24 + 'px';
        dragAndDrop.startY += 24;
      }
     // nextItem = dragAndDrop.nextItem(nextItem);
    }
    var previousItem = dragAndDrop.previousItem(dragAndDrop.curElement);
    if (previousItem != null) {
      var bottomMargin = dragAndDrop.rightBottomOffset(previousItem).offsetBottom;
      if (event.clientY <= bottomMargin) {
        dragAndDrop.moveBefore(previousItem, nextItem);
        element.style.top = event.clientY - startY + 24 + 'px';
        dragAndDrop.startY -= 24;
      }
    }
    event.stopPropagation();
  },

  dragEnd: function() {
    this.style.top = 0;
    this.style.zIndex = 10;
    this.style.cursor = 'pointer';
    dragAndDrop.isMouseDown = false;
    if (dragAndDrop.isMouseMove) {
      var nodes = this.parentNode.childNodes;
      var list = [];
      for (var i = 0; i < nodes.length; i++) {
        list.push(nodes[i].value);
      }
      localStorage['quicklyVisitMenu'] = list.join(',');
    }
  },

  onClick: function(shortcut) {
    if (!dragAndDrop.isMouseMove) {
      bg.plugin.triggerChromeShortcuts(shortcut);
      window.close();
    }
    dragAndDrop.isMouseMove = false;
  }
}
