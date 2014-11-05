Qt.include("DocumentFactory.js");

//Some of this code was taken from http://developer.nokia.com/community/wiki/How-to_create_a_persistent_settings_database_in_Qt_Quick_%28QML%29


function saveDocumentsToSql(documentHolder) {
	console.log("[QML]: Saving documents to SQL ...");
	var newDate = new Date();
	newDate.setTime(Date.now());
	var dateString = newDate.toISOString();

	console.log("[QML]: Saving documents to SQL...");

	initialize();

	for(var i in documentHolder.children) {
		if(documentHolder.children[i].objectName == "LayoutObject") {
			writeDocument(dateString,
						  documentHolder.children[i].filepath,
						  documentHolder.children[i].rotation,
						  documentHolder.children[i].centerX,
						  documentHolder.children[i].centerY,
						  documentHolder.children[i].z);
		}
	}
	console.log("[QML]: Saved documents to SQL. Key: " + dateString);
}


function loadDocumentsFromSql(saveTime, documentHolder, layoutScene) {
	console.log("[QML]: Loading documents from SQL. Key: " + saveTime);
	var documentProperties = getDocumentProperties(saveTime);
	if(documentProperties == "Unknown") {
		console.log("[QML]: Could not load document positions from Database");
		return;
	}
	for(var i = 0; i < documentProperties.length; i++) {
		createDocumentByKnownProperties(
					documentHolder,
					documentProperties.item(i).filePath,
					documentProperties.item(i).rotation,
					documentProperties.item(i).z,
					documentProperties.item(i).x,
					documentProperties.item(i).y,
					layoutScene);
	}
}

function getDatabase() {
	 return Sql.LocalStorage.openDatabaseSync("meshDemo", "1.0", "StorageDatabase", 100000);
}

function initialize() {
	var db = getDatabase();
	db.transaction(
		function(tx) {
			tx.executeSql('CREATE TABLE IF NOT EXISTS documents(id INTEGER PRIMARY KEY AUTOINCREMENT, \
																saveTime TEXT, \
																filePath TEXT, \
																rotation float,
																x float, y float,
																z int)');
	  });
}

function clearDatabase() {
	var db = getDatabase();
	db.transaction(
		function(tx) {
			tx.executeSql('DROP TABLE documents');
	  });

}

function writeDocument(saveTime, filePath, rotation, x, y, z) {
   var db = getDatabase();
   db.transaction(function(tx) {
	   var rs = tx.executeSql('INSERT INTO documents (saveTime, filePath, rotation, x, y, z)\
								VALUES (?,?,?,?,?,?);', [saveTime, filePath, rotation, x, y, z]);
			  if (!(rs.rowsAffected > 0))
				console.log("[QML]: Could not save document position to SQL")
		}
  );
}
function getDocumentProperties(saveTime) {
   var db = getDatabase();
   var res = "";
   db.transaction(function(tx) {
	 var rs = tx.executeSql('SELECT filePath, rotation, x, y, z\
							 FROM documents WHERE saveTime=?;', saveTime);
	 if (rs.rows.length > 0) {
		 res = rs.rows;
	 } else {
		 res = "Unknown";
	 }
  })
  // The function returns “Unknown” if the setting was not found in the database
  return res
}
