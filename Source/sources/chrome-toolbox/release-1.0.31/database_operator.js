var database = openDatabase("convenience_database", "1.0", "convenience", 5*1024*1024);

var db = {
  executeSqlCommand: function(sql, args, callBack) {
    if (database) {
      database.transaction(function(tx) {
        tx.executeSql(sql, args, callBack, db.logger);
      });
    } else {
      console.log('fail');
    }
  },

  logger: function(tx, error) {
    console.log(error.message);
  }
};

