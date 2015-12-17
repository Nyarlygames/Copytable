// ==UserScript==
// @name        View history
// @include     URLMANTIS*
// @require http://ajax.googleapis.com/ajax/libs/jquery/1.9.1/jquery.min.js
// ==/UserScript==

this.$ = this.jQuery = jQuery.noConflict(true);
$(document).ready(function()
{
    var historylist = $('<div>');
    $('td:nth-child(2)').each(function() // #column for id = 2
                              {
        var elt2 = $(this);
        var id = $(this).text();
        if (elt2.text().match('[0-9]')) {
            $.ajax(elt2.find('a').attr('href'), {context:elt2}).success(function(data) {
                var bugnote = $('<p>');
                var elt = $(this);
                elt.data('html', []);
                $(data).find('.small-caption').each(function(){
                    if ($(this).text().match("2015")) {
                        if (!$(this).text().match("File")) {
                            bugnote.append(id);
                            bugnote.append($(this).text());
                            
                            var reporter = $(this).next('td');
                            bugnote.append(reporter.text());
                            
                            var field = reporter.next('td');
                            bugnote.append(field.text());
                            
                            
                            var change = field.next('td');
                            bugnote.append(change.text() + '\n');
                        }
                    }
                });
                historylist.append(bugnote.html());
                elt.data('html').push(historylist.html());
                
                elt.mouseover(function()  {
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
                elt.mouseout(function() {
                    $(this).find('.myhistory').remove();
                });
            });
        }
    
    
    });

    
    
    
});