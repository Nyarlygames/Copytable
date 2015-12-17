// -------------------------------------------------------------- Search function
function Search(){
  
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var ssdb = SpreadsheetApp.getActiveSpreadsheet().getSheetByName("dbMantis");
  var rangedb = ssdb.getRange(2, 1,ssdb.getLastRow()-1,ssdb.getLastColumn());
  var rangefilters = ssdb.getRange(1, 1,ssdb.getLastRow(),ssdb.getLastColumn());
  var valuefilter = rangefilters.getValues();
  var valuedb = rangedb.getValues();
  var active = ss.getActiveRange();
  var cols = 0;
  var foundlist = new Array(active.getHeight());
  var filterlist = new Array(rangefilters.getWidth());
  var colsfilter = 0;
  var filtercount = 0;
  var countFilternb = 0;
  var tempFilter = new Array(rangefilters.getWidth());
  var tempCol = 0;
  var unique = 0;
  
  while ( cols < active.getWidth()) {
    // populate filter is list
      var activecell2 = active.getCell(1, (cols+1) );
    
    while (colsfilter < rangefilters.getWidth()) {
      if (valuefilter[0][colsfilter] == activecell2.getValue()) {
        filterlist[filtercount] = colsfilter;
        filtercount++;
      }
      colsfilter ++;
    }
    colsfilter = 0;
    cols++;
  }
  // get unique filter count
  cols = 0;
  while (cols < filtercount) {
    while (tempCol < filtercount) {
      if ((tempFilter[tempCol] == filterlist[cols]) && (cols != tempCol)) {
        unique++;
      }
      tempCol++;
    }
    if (unique == 0) {
      tempFilter[countFilternb] = filterlist[cols];
      countFilternb++;
    }
    unique=0;
    tempCol=0;
    cols++;
  }
  

  cols = 0;
  var rows = 1;
  var foundcount = 0;
  var foundperrow = 0;
      // browse through all active rows
      active.getCell(1, active.getWidth()).offset(0,1).setValue("Count"); 
      active.getCell(1, active.getWidth()).offset(0,2).setValue("List");   
  while (rows < active.getHeight()) { 
    foundlist[rows] = "Mantis : ";
    // browse through all db
      for (var rowdb in valuedb) {
        // check db value with current cell
        while ( cols < active.getWidth()) {
          var activecell = active.getCell(rows+1, cols+1).getValue();
          if ((activecell != "") && (activecell != "All")) {
              // ---------------------- Number ---------------------- //
            if (IsNumeric(activecell)) {
              if (valuedb[rowdb][filterlist[cols]] == activecell) {
                foundcount++;
              }              
            }
            else if (IsDate(activecell)) {
              
              // ---------------------- Date to handle ---------------------- //
             /* var Datedb = new Date(valuedb[rowdb][filterlist[cols]]);
              var Datebase = new Date(activecell2);
                ss.getRange('A1').setValue(Datedb);
              if (Date == activecell2) {
                ss.getRange('A3').setValue("test");
              }*/
            }
              // ---------------------- Text ---------------------- //
            else if (valuedb[rowdb][filterlist[cols]].match(activecell)) {
              foundcount++;
            }
          }
          else if (activecell == "All"){
          /*  // si case vide & col label est unique
            while (duplicatecols < maxfoundperrow) {
              if (active.getCell(1,
            }*/
            foundcount++;
          }
          cols++
        }
        // db item matches all filters
        if (foundcount == countFilternb) {
          foundperrow++;
          foundlist[rows] += "\n" + valuedb[rowdb][0] + "	" + valuedb[rowdb][19];
        }
        foundcount = 0;  
        cols = 0;
      }
    // display results or empty string if no results
    if (foundlist[rows] != "") {
      active.getCell(rows+1, active.getWidth()).offset(0,1).setValue(foundperrow);   
      active.getCell(rows+1, active.getWidth()).offset(0,2).setValue(foundlist[rows]);    
    }
    else {
      active.getCell(rows+1, active.getWidth()).offset(0,1).setValue("0"); 
      active.getCell(rows+1, active.getWidth()).offset(0,2).setValue("");
    }
    foundperrow = 0;
    rows++;
  }
}
 
// -------------------------------------------------------------- HighLevel function
function SearchTool() { // choose a range in sheet
 var ss = SpreadsheetApp.getActiveSpreadsheet().getSheetByName("TestHighAuto");
 var cellbase = ss.getRange('D1');
 var cellcount = ss.getRange('B2');
  // clean la page
 var cellclean = ss.getRange(1, 1,ss.getLastRow(),4);
 cellbase.setValue("Cleaning");
 cellclean.clear({contentsOnly: true});
  var labelfilter1 = ss.getRange('G1').getValue();
  var labelfilter2 = ss.getRange('I1').getValue();
  var labelfilter3 = ss.getRange('K1').getValue();
  var labelmod = ss.getRange('M1').getValue();
  var labelproject = ss.getRange('O1').getValue();
  
  var filtre_base = "Category";//filtre_base
  var filtre1 = ss.getRange(1,8).getValue();//repro
  var filtre2 = ss.getRange(1,10).getValue();//severity
  var filtre3 = ss.getRange(1,12).getValue();//status
  var mod = ss.getRange(1,14).getValue();//mod 
  var project = ss.getRange(1,16).getValue();//project
  var textmajor = filtre2 + " list :  ";
cellbase.setValue(cellbase.getValue() + "\n" +  "Selecting project");
  switch (project) {
    case "Mordheim":
 var ssdb = SpreadsheetApp.getActiveSpreadsheet().getSheetByName("dbMordheim");
 var listcat = ss.getRange('A2').setFormula("=UNIQUE(dbMordheim!J2:J)"); // compile la liste des catégories
 var countCatnb = ss.getRange('F1').setFormula("=COUNTUNIQUE(dbMordheim!J2:J)");
  var maxcat = ss.getRange('F1').getValue();
      ss.getRange('A1').setValue("Nb categories : "  + maxcat);
      break;
    case "BFG":
 var ssdb = SpreadsheetApp.getActiveSpreadsheet().getSheetByName("dbBFG");
 var listcat = ss.getRange('A2').setFormula("=UNIQUE(dbBFG!J2:J)"); // compile la liste des catégories
 var countCatnb = ss.getRange('F1').setFormula("=COUNTUNIQUE(dbBFG!J2:J)");
  var maxcat = ss.getRange('F1').getValue();
      ss.getRange('A1').setValue("Nb categories : "  + maxcat);
      break;
    case "TTM":
 var ssdb = SpreadsheetApp.getActiveSpreadsheet().getSheetByName("dbTTM");
 var listcat = ss.getRange('A2').setFormula("=UNIQUE(dbTTM!J2:J)"); // compile la liste des catégories
 var countCatnb = ss.getRange('F1').setFormula("=COUNTUNIQUE(dbTTM!J2:J)");
  var maxcat = ss.getRange('F1').getValue();
      ss.getRange('A1').setValue("Nb categories : "  + maxcat);
      break;
    case "BB2":
 var ssdb = SpreadsheetApp.getActiveSpreadsheet().getSheetByName("dbBB2");
 var listcat = ss.getRange('A2').setFormula("=UNIQUE(dbBB2!J2:J)"); // compile la liste des catégories
 var countCatnb = ss.getRange('F1').setFormula("=COUNTUNIQUE(dbBB2!J2:J)");
  var maxcat = ss.getRange('F1').getValue();
      ss.getRange('A1').setValue("Nb categories : " + + maxcat);
      break;
    case "SAF":
 var ssdb = SpreadsheetApp.getActiveSpreadsheet().getSheetByName("dbSAF");
 var listcat = ss.getRange('A2').setFormula("=UNIQUE(dbSAF!J2:J)"); // compile la liste des catégories
 var countCatnb = ss.getRange('F1').setFormula("=COUNTUNIQUE(dbSAF!J2:J)");
  var maxcat = ss.getRange('F1').getValue();
      ss.getRange('A1').setValue("Nb categories : "  + maxcat);
      break;
    case "FS15":
 var ssdb = SpreadsheetApp.getActiveSpreadsheet().getSheetByName("dbFS15");
 var listcat = ss.getRange('A2').setFormula("=UNIQUE(dbFS15!J2:J)"); // compile la liste des catégories
 var countCatnb = ss.getRange('F1').setFormula("=COUNTUNIQUE(dbFS15!J2:J)");
  var maxcat = ss.getRange('F1').getValue();
      ss.getRange('A1').setValue("Nb categories : "  + maxcat);
      break;
    case "TDF16":
 var ssdb = SpreadsheetApp.getActiveSpreadsheet().getSheetByName("dbTDF16");
 var listcat = ss.getRange('A2').setFormula("=UNIQUE(dbTDF16!J2:J)"); // compile la liste des catégories
 var countCatnb = ss.getRange('F1').setFormula("=COUNTUNIQUE(dbTDF16!J2:J)");
  var maxcat = ss.getRange('F1').getValue();
      ss.getRange('A1').setValue("Nb categories : " + maxcat);
      break;
    case "All Focus":
 var ssdb = SpreadsheetApp.getActiveSpreadsheet().getSheetByName("dbMantisFocus");
 var listcat = ss.getRange('A2').setFormula("=UNIQUE(dbMantisFocus!J2:J)"); // compile la liste des catégories
 var countCatnb = ss.getRange('F1').setFormula("=COUNTUNIQUE(dbMantisFocus!J2:J)");
  var maxcat = ss.getRange('F1').getValue();
      ss.getRange('A1').setValue("Nb categories : " + maxcat);
      break;
    case "All Cyanide":
 var ssdb = SpreadsheetApp.getActiveSpreadsheet().getSheetByName("dbMantisCyanide");
 var listcat = ss.getRange('A2').setFormula("=UNIQUE(dbMantisCyanide!J2:J)"); // compile la liste des catégories
 var countCatnb = ss.getRange('F1').setFormula("=COUNTUNIQUE(dbMantisCyanide!J2:J)");
  var maxcat = ss.getRange('F1').getValue();
      ss.getRange('A1').setValue("Nb categories : " + maxcat);
      break;
    case "Full":
 var ssdb = SpreadsheetApp.getActiveSpreadsheet().getSheetByName("dbMantis");
 var listcat = ss.getRange('A2').setFormula("=UNIQUE(dbMantis!J2:J)"); // compile la liste des catégories
 var countCatnb = ss.getRange('F1').setFormula("=COUNTUNIQUE(dbMantis!J2:J)");
  var maxcat = ss.getRange('F1').getValue();
      ss.getRange('A1').setValue("Nb categories : " + maxcat);
      break;
    default:
      break;
  }
  
cellbase.setValue(cellbase.getValue() + "\n" +  "Setting variables");
 var celldb = ssdb.getRange('A2');

 var rowbase = 0;
 var row = 2;
 var rangedb = ssdb.getRange(row, 1,ssdb.getLastRow()-1,ssdb.getLastColumn());
 var valuedb = rangedb.getValues();
  cellbase.setValue(cellbase.getValue() + "\n" +  "Determining max unique filtre1");
 var rangecat = ss.getRange(2,1,ss.getLastRow() ,ss.getLastColumn()); // l'affiche
cellbase.setValue(cellbase.getValue() + "\n" +  "Chaos is at work, please be patient...");
 var valuecat = rangecat.getValues();
 var indexes = new Array(maxcat); // all category
  var majorcount = 0;
  var majortotal = 0;
 var catcount = 0;
 var catotal = 0;
  var boolrow = -1;
  var catuniques=0;
 var majorlist = new Array(maxcat); // all categor
  // init tableau catégorie
             cellbase.setValue(cellbase.getValue() + "\n" +  "Parsing categories");
   for (var id in valuecat) {
     if (rowbase < maxcat) {
     indexes[rowbase] = valuecat[id][0];
         majorlist[rowbase] = "";
     
     // loop pour count
     for (var rows in valuedb) {
       
       if (valuedb[rows][9] == indexes[rowbase]) {
         catcount++;
         catotal++;
         
         switch (filtre3) {
           case "non-resolved":
                      switch (filtre1){
           case "always": 
             if ((valuedb[rows][6] == filtre1) && ((valuedb[rows][7]=="new") || (valuedb[rows][7]=="assigned") ||  (valuedb[rows][7]=="feedback") || (valuedb[rows][7]=="acknowledged")))  {
               switch (filtre2){
                 case "Must":
                   if ((valuedb[rows][25] == filtre2)) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "major":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "block":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "crash":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "minor":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "minorless":
                   if (valuedb[rows][5] != "minor") {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "all":
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   break;
                 default:
                   break;
               }
             }
             break;
           case "unable": 
             if ((valuedb[rows][6] == "unable to reproduce") && ((valuedb[rows][7]=="new") || (valuedb[rows][7]=="assigned") ||  (valuedb[rows][7]=="feedback") || (valuedb[rows][7]=="acknowledged"))) {
               switch (filtre2){
                 case "Must":
                   if (valuedb[rows][25] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "major":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "block":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "crash":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "minor":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "minorless":
                   if (valuedb[rows][5] != "minor") {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "all":
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   break;
                 default:
                   break;
               }
             }
             break;
             case "All": 
             if ((valuedb[rows][7]==filtre3) && (valuedb[rows][7]=="new") || (valuedb[rows][7]=="assigned") ||  (valuedb[rows][7]=="feedback") || (valuedb[rows][7]=="acknowledged")) {
               switch (filtre2){
                 case "Must":
                   if (valuedb[rows][25] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "major":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "block":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "crash":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "minor":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "minorless":
                   if (valuedb[rows][5] != "minor") {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "all":
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   break;
                 default:
                   break;
               }}
             break;
           default: 
             if ((valuedb[rows][6] == filtre1) && (valuedb[rows][7]=="new") || (valuedb[rows][7]=="assigned") ||  (valuedb[rows][7]=="feedback") || (valuedb[rows][7]=="acknowledged")) {
               switch (filtre2){
                 case "Must":
                   if (valuedb[rows][25] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "major":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "block":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "crash":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "minor":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "minorless":
                   if (valuedb[rows][5] != "minor") {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "all":
                   majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                   majorcount++;
                   majortotal++;
                   break;
                 default:
                   break;
               }
             }
                          
             break;
         }
             break;
           case "All":
                  switch (filtre1){
           case "always": 
             if ((valuedb[rows][6] == filtre1))  {
               switch (filtre2){
                 case "Must":
                   if ((valuedb[rows][25] == filtre2)) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "major":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "block":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "crash":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "minor":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "minorless":
                   if (valuedb[rows][5] != "minor") {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "all":
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   break;
                 default:
                   break;
               }
             }
             break;
           case "unable": 
             if ((valuedb[rows][6] == "unable to reproduce"))  {
               switch (filtre2){
                 case "Must":
                   if (valuedb[rows][25] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "major":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "block":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "crash":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "minor":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "minorless":
                   if (valuedb[rows][5] != "minor") {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "all":
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   break;
                 default:
                   break;
               }
             }
             break;
             case "All": 
               switch (filtre2){
                 case "Must":
                   if (valuedb[rows][25] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "major":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "block":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "crash":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "minor":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "minorless":
                   if (valuedb[rows][5] != "minor") {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "all":
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   break;
                 default:
                   break;
               }
             break;
           default: 
             if ((valuedb[rows][6] == filtre1))  {
               switch (filtre2){
                 case "Must":
                   if (valuedb[rows][25] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "major":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "block":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "crash":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "minor":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "minorless":
                   if (valuedb[rows][5] != "minor") {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "all":
                   majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                   majorcount++;
                   majortotal++;
                   break;
                 default:
                   break;
               }
             }
             break;
         }
             break;
           default:         switch (filtre1){
           case "always": 
             if ((valuedb[rows][6] == filtre1) && (valuedb[rows][7]==filtre3))  {
               switch (filtre2){
                 case "Must":
                   if ((valuedb[rows][25] == filtre2)) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "major":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "block":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "crash":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "minor":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "minorless":
                   if (valuedb[rows][5] != "minor") {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "all":
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   break;
                 default:
                   break;
               }
             }
             break;
           case "unable": 
             if ((valuedb[rows][6] == "unable to reproduce") && (valuedb[rows][7]==filtre3))  {
               switch (filtre2){
                 case "Must":
                   if (valuedb[rows][25] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "major":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "block":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "crash":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "minor":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "minorless":
                   if (valuedb[rows][5] != "minor") {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "all":
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   break;
                 default:
                   break;
               }
             }
             break;
             case "All": 
             if (valuedb[rows][7]==filtre3) {
               switch (filtre2){
                 case "Must":
                   if (valuedb[rows][25] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "major":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "block":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "crash":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "minor":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "minorless":
                   if (valuedb[rows][5] != "minor") {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "all":
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   break;
                 default:
                   break;
               }}
             break;
           default: 
             if ((valuedb[rows][6] == filtre1) && (valuedb[rows][7]==filtre3))  {
               switch (filtre2){
                 case "Must":
                   if (valuedb[rows][25] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "major":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "block":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "crash":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "minor":
                   if (valuedb[rows][5] == filtre2) {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "minorless":
                   if (valuedb[rows][5] != "minor") {
                     majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                     majorcount++;
                     majortotal++;
                   }
                   break;
                 case "all":
                   majorlist[rowbase] += "\n" + valuedb[rows][0]+ "	" +valuedb[rows][19];
                   majorcount++;
                   majortotal++;
                   break;
                 default:
                   break;
               }
             }
             break;
         }
             break;

         }
       }
       switch (mod) {
         case "nolist" :
           if (majorcount > 0) {
         cellcount.offset(id,2).setValue("Ko");
           }
           else {
         cellcount.offset(id,2).setValue("Pass");
           }   
           break;
         case "full":
           if (majorcount > 0) {
         cellcount.offset(id,2).setValue(textmajor + majorlist[rowbase]);
           }
           else {
         cellcount.offset(id,2).setValue("Pass");
           }          
           break
       }
      // textmajor = "";
       
     }
     cellcount.offset(id,0).setValue(catcount); //nb par catégorie
     cellcount.offset(id,1).setValue(majorcount); // nb major count par catégory
     catcount = 0;
       if (majorcount>0)
             cellcount.offset(id,2).setFontSize(8);
       else
             cellcount.offset(id,2).setFontSize(10);
     majorcount = 0;
     rowbase++; 
     }
   }
             cellbase.setValue(cellbase.getValue() + "\n" +  "Displaying totals");
  ss.getRange(1,3).setValue("Total issues found " +majortotal);
  ss.getRange('B1').setValue("Total issues : " + catotal);
  ss.getRange('F1').setValue("Case tampon");
  
  cellbase.setValue(labelproject+ " : " + project + "\n" + labelfilter2+ " : " + filtre2 + "\n"+ labelfilter1 + " : " + filtre1+"\n"+ labelfilter3 + " : " + filtre3+"\n"+ labelmod + " : " + mod);              
  cellbase.setFontSize(8);
}

// -------------------------------------------------------------- Debug history

function myHisto() {
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var rangeresults = ss.getRange('A2');
  var sshisto = SpreadsheetApp.getActiveSpreadsheet().getSheetByName("HistoMantis");
  var rangehisto = sshisto.getRange(2, 1,sshisto.getLastRow(),sshisto.getLastColumn());
  var valuehisto = rangehisto.getValues();
  var foundclosed = 0;
  var foundopen = 0;
  var foundate = 0;
  var uniquedate = new Array(rangehisto.getWidth());
  var newarr = new Array(rangehisto.getWidth());
  var closearr = new Array(rangehisto.getWidth());
  
  
  
  var isunique = 0;
  for (var fields in valuehisto) {
    
    if (valuehisto[fields][4].match("=> closed")){
      for (var knowndate in uniquedate) {
        if (valuehisto[fields][1].valueOf() == uniquedate[knowndate].valueOf()) {
          closearr[knowndate]++;
          isunique++;
        }
      }
      if (isunique == 0) {
        uniquedate[foundate] = valuehisto[fields][1];
        closearr[foundate] = 1;
        newarr[foundate] = 0;
        foundate++;
      }
      isunique = 0;
    }
    
    if (valuehisto[fields][3].match("New Issue")){
      for (var knowndate in uniquedate) {
        if (valuehisto[fields][1].valueOf() == uniquedate[knowndate].valueOf()) {
          newarr[knowndate]++;
          isunique++;
        }
      }
      if (isunique == 0) {
        uniquedate[foundate] = valuehisto[fields][1];
        newarr[foundate] = 1;
        closearr[foundate] = 0;
        foundate++;
      }
      isunique = 0;
    }
  }
  
  for (var display in uniquedate) {
    rangeresults.offset(display,0).setValue(uniquedate[display]);
    rangeresults.offset(display,1).setValue(closearr[display]);
    rangeresults.offset(display,2).setValue(newarr[display]);
  }
}