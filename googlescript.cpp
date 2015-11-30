function List_from_db() { // choose a range in sheet
 var ss = SpreadsheetApp.getActiveSpreadsheet();
 var cellclean = ss.getRange("A2:E9999");
 var cellbase = ss.getRange('A2');
 cellclean.clear({contentsOnly: true});
  
 var ssdb = SpreadsheetApp.getActiveSpreadsheet().getSheetByName("dbMantis");
 var celldb = ssdb.getRange('A2');

 var rowbase = 0;
 var row = 2;
 var rangedb = ssdb.getRange(row, 1,ssdb.getLastRow(),ssdb.getLastColumn());
 var valuedb = rangedb.getValues();
 var severity = ss.getRange('H4').getValue()
    
   for (var rows in valuedb) {
     if (valuedb[rows][5] == severity) {
      cellbase.offset(rowbase, 0).setValue(valuedb[rows][0]); // id 
      cellbase.offset(rowbase, 1).setValue(valuedb[rows][7]); // status
      cellbase.offset(rowbase, 2).setValue(valuedb[rows][6]); // reproducibility
      cellbase.offset(rowbase, 3).setValue(valuedb[rows][5]); // severity
      cellbase.offset(rowbase, 4).setValue(valuedb[rows][19]); // summary
      rowbase++
     }
    }
}

function ExportHigh() { // choose a range in sheet
 var ss = SpreadsheetApp.getActiveSpreadsheet().getSheetByName("TestHighAuto");
 var cellbase = ss.getRange('A2');
 var cellcount = ss.getRange('B2');
  // clean la page
 var cellclean = ss.getRange(2, 1,ss.getLastRow(),ss.getLastColumn());
 cellclean.clear({contentsOnly: true});
  
 var ssdb = SpreadsheetApp.getActiveSpreadsheet().getSheetByName("dbMantis");
 var celldb = ssdb.getRange('A2');

 var rowbase = 0;
 var row = 2;
 var rangedb = ssdb.getRange(row, 1,ssdb.getLastRow(),ssdb.getLastColumn());
 var valuedb = rangedb.getValues();
 //var severity = ss.getRange('H4').getValue()
// var countCatnb = ss.getRange('A1').setFormula("=COUNTUNIQUE(dbMantis!J2:J)");
 var countCatnb = ss.getRange('B1').setFormula("=COUNTUNIQUE(dbMantis!J2:J)");
  var maxcat = ss.getRange('B1').getValue();
  //var countCatnb = ss.getRange(maxcat + 2,2).setValue(ss.getRange('B1').getValue());
 var countCatlabel = ss.getRange('B1').setValue("Nb category : " + ss.getRange('B1').getValue());
  "Nb category : "
 var listcat = ss.getRange('A2').setFormula("=UNIQUE(dbMantis!J2:J)"); // compile la liste des catégories
 var rangecat = ss.getRange(2,1,ss.getLastRow() - 1,ss.getLastColumn()); // l'affiche
 var valuecat = rangecat.getValues();
 var indexes = new Array(maxcat); // all category
  var majorcount = 0;
  var majortotal = 0;
 var catcount = 0;
 var catotal = 0;
  var filtre1 = ss.getRange(1,8).getValue();//filtre1
  var filtre2 = ss.getRange(1,10).getValue();//filtre2
  var mod = ss.getRange(1,12).getValue();//mod 
  var textmajor = filtre2 + " list :  ";
 var majorlist = new Array(maxcat); // all category
  // init tableau catégorie
   for (var id in valuecat) {
     indexes[rowbase] = valuecat[id][0];
     
     // loop pour count
     for (var rows in valuedb) {
       if (valuedb[rows][9] == indexes[rowbase]) {
         catcount++;
         catotal++;
         
         switch (filtre2){
           case "Must":
             if (valuedb[rows][25] == filtre2) {
               textmajor += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
               majorcount++;
               majortotal++;
             }
             break;
           case "major":
             if (valuedb[rows][5] == filtre2) {
               textmajor += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
               majorcount++;
               majortotal++;
             }
             break;
           case "block":
             if (valuedb[rows][5] == filtre2) {
               textmajor += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
               majorcount++;
               majortotal++;
             }
             break;
           case "minorless":
          //   if ((valuedb[rows][5] == "major") || (valuedb[rows[5] == "block")  || (valuedb[rows[5] == "crash")) {
             if ((valuedb[rows][5] == "major") || (valuedb[rows][5] == "block") || (valuedb[rows][5] == "crash")) {
               textmajor += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
               majorcount++;
               majortotal++;
             }
             break;
           default:
             break;
         }
 //        cellcount.offset(id,1).setValue(cellcount.offset(id,1).getValue() + valuedb[rows][5]);

       }
       majorlist[rowbase] = textmajor;
         cellcount.offset(id,2).setValue(majorlist[rowbase]);
      // textmajor = "";
       
     }
     cellcount.offset(id,0).setValue(catcount); //nb par catégorie
     cellcount.offset(id,1).setValue(majorcount); // nb major count par catégory
      /*debug*/
   //cellcount.offset(id,1).setValue(indexes[rowbase]);
    // cellcount.offset(id,2).setValue("rowbase" + rowbase + " id " + id + "catcount : " + catcount);
     
     // on affiche le compte à côté de chaque catégorie
     catcount = 0;
     majorcount = 0;
     rowbase++;
   }
  ss.getRange(1,3).setValue("Nombre de " + filtre2 + " :	" +majortotal);
  ss.getRange('B1').setValue("Total category : " + catotal);
//  countCatnb = "";
}







