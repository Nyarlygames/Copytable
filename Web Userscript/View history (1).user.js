// ==UserScript==
// @name        View history
// @include     http://mantisurl/view_all_bug_page.php*
// @require		http://ajax.googleapis.com/ajax/libs/jquery/1.9.1/jquery.min.js
// ==/UserScript==

this.$ = this.jQuery = jQuery.noConflict(true);
$(document).ready(function()
{	
    var curcat = 1;
    var id = 1;
   $('tr.row-category').each(function() 
	{ 
       $(this).find('td').each (function() {
           var elt = $(this);
           if (elt.text().match("ID")) {
               id = curcat;
           }
           else  {
               curcat++;
           }
       });
   });
        $('td:nth-child('+ id + ')').each(function() // colonne ID
                                         {
            elt = $(this);
            //	if (elt.text().match('[0-9]')) // si il y a des commentaires
            //	{
            $.ajax(elt.find('a').attr('href'), {context:elt}).success(function(data) // on fait un appel ajax sur l'url du lien
                                                                      {
                var elt = $(this);
                elt.data('html', []);
                $(data).find('.small-caption').each(function() // on cherche ll'historique
                                                    {
                    var bugnote = $('<div>');
                    if ($(this).text().match("2015")) {
                        if (!$(this).text().match("File")) {
                            bugnote.append($(this).html());
                            var reporter = $(this).next('td');
                            bugnote.append(reporter.html());
                            var field = reporter.next('td');
                            bugnote.append(field.html());
                            var change = field.next('td');
                            bugnote.append(change.html());
                            elt.data('html').push(bugnote.html());
                        }
                    }
                });

                elt.mouseover(function() // on affiche une infobox au survol de souris
                              {
                    var box = $('<div>');
                    box.addClass('myhistory');
                    box.html(elt.data('html').join('<hr/>'));
                    box.css('position', 'absolute');
                    box.css('width', '800px');
                    box.css('border', '2px solid black');
                    box.css('text-align', 'left');
                    box.css('background-color', '#fff');
                    $(this).append(box);
                });
                elt.mouseout(function() // on enlève l'infobox quand on se barre
                             {
                    $(this).find('.myhistory').remove();
                });
            });
            //	}
        });
});