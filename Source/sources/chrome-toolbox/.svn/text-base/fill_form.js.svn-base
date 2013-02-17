var FillForm = function() {
}

FillForm.prototype.createTable = function() {
  var sql = 'create table if not exists fillForm_table(' +
              'id integer primary key,' +
              'url varchar,' +
              'title varchar,' +
              'formInfo text,' +
              'date datetime)';
  db.executeSqlCommand(sql, null, null);
};

FillForm.prototype.showContentById = function(id) {
  var sql = 'select * from fillForm_table where id = ?';
  db.executeSqlCommand(sql, [id], function(tx, results) {
    if (results.rows.length > 0) {
      var title_field = chrome.i18n.getMessage('fill_form_field');
      var title_content = chrome.i18n.getMessage('fill_form_content');
      var title_type = chrome.i18n.getMessage('fill_form_type');
      var title = document.getElementById('divTitle');
      var url = document.getElementById('divURL');
      title.innerText = 'Title:'+results.rows.item(0).title;
      url.innerText = 'URL:' + results.rows.item(0).url;
      var formInfo = JSON.parse(results.rows.item(0).formInfo);
      var table = '';
      table = '<table id="tt" cellpadding="0" cellspacing="0" border="0"> '+
              '<thead>' +
              '<tr>' +
              '<td style="width:160px;">' + title_field + '</td>' +
              '<td style="width:300px;">' + title_content +'</td>' +
              '<td style="width:105px;">' + title_type + '</td>' +
              '</tr>' +
              '</thead>';
      for (var i = 0; i < formInfo.length; i++) {
        table += '<tr>' +
                 '<td>' + (formInfo[i].id || formInfo[i].name) + '</td>' +
                 '<td>' + formInfo[i].value + '</td>' +
                 '<td>' + formInfo[i].type + '</td>' +
                 '</tr>';
      }
      table += '</table>';
     
      $('divFromInfoTable').innerHTML = table;
      $('formContent').style.left = window.innerWidth/2 - 250 + 'px';
      $('formContent').style.display = 'block';
    }
  });
};

FillForm.prototype.showAllFormDate = function(){
  var sql = 'select * from fillForm_table';
  var table = '';
  db.executeSqlCommand(sql, null, function(tx, results) {
    table = '<table border="0" cellspacing="0" cellpadding="0">';
    for (var i = 0; i < results.rows.length; i++) {
      var id = results.rows.item(i).id;
      var title = results.rows.item(i).title;
      var url = results.rows.item(i).url;
      var date = results.rows.item(i).date;
      var viewText = chrome.i18n.getMessage('fill_form_view');
      var delText = chrome.i18n.getMessage('fill_form_delete');
      table += '<tr>' +
          '<td><div class="fillForm_url"><a href="' + url +
          '" target="_blank">' + url + '</a></div></td>' +
          '<td><div class="fillForm_title">' + title + '</div></td>' +
          '<td><div class="fillForm_date">' + date + '</div></td>' +
          '<td><div class="fillForm_operate"><a href="#" ' +
          'onclick="fillForm.showContentById(' + id +
          ')">' + viewText + '</a> <a href="#" onclick="fillForm.deleteById('+
          id + ');fillForm.showAllFormDate();">' + delText + '</a></div>' +
          '</tr>';
    }
    table += '</table>';
    document.getElementById('allFormInfo').innerHTML = table;
  });
};

FillForm.prototype.deleteAllData = function() {
  var sql = 'delete from fillForm_table';
  db.executeSqlCommand(sql, null, null);
};

FillForm.prototype.deleteById = function(id) {
  var sql = 'delete from fillForm_table where id = ?';
  db.executeSqlCommand(sql, [id], null);
};

FillForm.prototype.deleteByUrl = function(url) {
  var sql = 'delete from fillForm_table where url = ?';
  db.executeSqlCommand(sql, [url], null);
};

FillForm.prototype.update = function(formInfo, title, id) {
  var sql = 'update fillForm_table set formInfo = ?, title = ?, date = ? where id = ?';
  db.executeSqlCommand(sql, [formInfo, title, getDate(), id], null);
};

FillForm.prototype.selectByUrl = function(url, callBack) {
  var sql = 'select * from fillForm_table where url = ?';
  db.executeSqlCommand(sql, [url], callBack);
};

FillForm.prototype.insert = function(url, title, formInfo) {
  var sql = 'insert into fillForm_table(url, title, formInfo, date)values(?, ?, ? ,?)';
  db.executeSqlCommand(sql, [url, title, formInfo, getDate()], null);
};



