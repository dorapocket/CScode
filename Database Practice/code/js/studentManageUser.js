
var scoredialog = new mdui.Dialog('#score-dialog');
var delsno, delname;
var modifyid,listdelid;

function score(id) {
    $.post("./modules/getScore.php",
        {
            Sno: id,
        },
        function (data, status) {
      var you=0;
      var liang=0;
      var zhong=0;
      var all=0;
            if (data.code == 200 && data.data.content.length > 0) {
                    $("#chips").empty();
                    $("#score_context").empty();
                    $("#score_name").text(data.data.student.Sname);
                    $("#score_sno").text(data.data.student.Sno);
                    var $sTemp = $("#score_context");
                    for (var i = 0; i < data.data.content.length; i++) {
                      all=all+1;
                        if(data.data.content[i].Score<60){
                            $sTemp.append("<div><span class=\"score-tit\">"+data.data.content[i].Cname+"：</span><span style=\"color:#f44336;\" class=\"score-inf\">"+data.data.content[i].Score+"</span></div>");
                        }else if(data.data.content[i].Score>=60&&(data.data.content[i].Score<75)){
                          zhong=zhong+1;
                            $sTemp.append("<div><span class=\"score-tit\">"+data.data.content[i].Cname+"：</span><span style=\"color:#fff176;\" class=\"score-inf\">"+data.data.content[i].Score+"</span></div>");
                        }else if(data.data.content[i].Score>=75&&(data.data.content[i].Score<85)){
                          liang=liang+1;
                            $sTemp.append("<div><span class=\"score-tit\">"+data.data.content[i].Cname+"：</span><span style=\"color:#cddc39;\" class=\"score-inf\">"+data.data.content[i].Score+"</span></div>");
                        }else{
                          you=you+1;
                            $sTemp.append("<div><span class=\"score-tit\">"+data.data.content[i].Cname+"：</span><span style=\"color:#4caf50;\" class=\"score-inf\">"+data.data.content[i].Score+"</span></div>");
                        }
                    }
                                  var $trTemp = $("<div></div>");
                    $trTemp.append("<div class=\"mdui-chip\"><span class=\"mdui-chip-title\">最高分："+data.data.basic.highest_C+" "+data.data.basic.highest_S+"</span></div>");
                    $trTemp.append("<div class=\"mdui-chip\"><span class=\"mdui-chip-title\">最低分："+data.data.basic.lowest_C+" "+data.data.basic.lowest_S+"</span></div>");
                    $trTemp.append("<div class=\"mdui-chip\"><span class=\"mdui-chip-title\">平均分："+data.data.basic.ave+"</span></div>");
                    $trTemp.append("<div class=\"mdui-chip\"><span class=\"mdui-chip-title\">及格/不及格："+(you+liang+zhong)+" ("+((you+liang+zhong)/all*100).toFixed(2)+"%)/"+(all-you-liang-zhong)+" ("+((all-you-liang-zhong)/all*100).toFixed(2)+"%)</span></div>");
              		$trTemp.append("<div class=\"mdui-chip\"><span class=\"mdui-chip-title\">优/良/中："+you+" ("+((you/all)*100).toFixed(2)+"%)"+"/"+liang+" ("+((liang/all)*100).toFixed(2)+"%)"+"/"+zhong+" ("+((zhong/all)*100).toFixed(2)+"%)"+"</span></div>");
                    $trTemp.appendTo("#chips");
                    //$sTemp.appendTo("#score_context");
                    mdui.mutation();
                    scoredialog.open();
            }
        }
    )
}
function flashdata() {
    $.post("./modules/searchStudent.php",
        {
            keywords: "",
        },
        function (data, status) {
            if (data.code == 200 && data.data.length > 0) {
                $("#table_data").empty();
                for (var i = 0; i < data.data.length; i++) {                //动态创建一个tr行标签,并且转换成jQuery对象
                    var $trTemp = $("<tr></tr>");                //往行里面追加 td单元格
                    $trTemp.append("<td>" + data.data[i][0] + "</td>");
                    $trTemp.append("<td>" + data.data[i][3] + "</td>");
                    $trTemp.append(data.data[i][1] == 0 ? "<td>男</td>" : "<td>女</td>");
                    $trTemp.append("<td>" + data.data[i][2] + "</td>");
                    $trTemp.append("<td><button onclick=\"score('" + data.data[i][0] + "')\" class=\"mdui-btn mdui-btn-icon mdui-ripple table-btn\"><i class=\"mdui-icon material-icons\">remove_red_eye</i></button></td>");
            
                    $trTemp.appendTo("#table_data");
                    mdui.mutation();
                }
            } else {
                $("#table_data").empty();
                var $trTemp = $("<tr></tr>");                //往行里面追加 td单元格
                $trTemp.append("<td>无</td>");
                $trTemp.append("<td>无</td>");
                $trTemp.append("<td>无</td>");
                $trTemp.append("<td>无</td>");
                $trTemp.append("<td></td>");

                $trTemp.appendTo("#table_data");
                mdui.mutation();
            }
        }
    )
}
$(document).ready(function () {
    flashdata();
    $("#search").bind("input propertychange", function (event) {
        $.post("./modules/searchStudent.php",
            {
                keywords: $("#search").val(),
            },
            function (data, status) {
                if (data.code == 200 && data.data.length > 0) {
                    $("#table_data").empty();
                    for (var i = 0; i < data.data.length; i++) {                //动态创建一个tr行标签,并且转换成jQuery对象
                        var $trTemp = $("<tr></tr>");                //往行里面追加 td单元格
                        $trTemp.append("<td>" + data.data[i][0] + "</td>");
                        $trTemp.append("<td>" + data.data[i][3] + "</td>");
                        $trTemp.append(data.data[i][1] == 0 ? "<td>男</td>" : "<td>女</td>");
                        $trTemp.append("<td>" + data.data[i][2] + "</td>");
                        $trTemp.append("<td><button onclick=\"score('" + data.data[i][0] + "')\" class=\"mdui-btn mdui-btn-icon mdui-ripple table-btn\"><i class=\"mdui-icon material-icons\">remove_red_eye</i></button></td>");
                        $trTemp.appendTo("#table_data");
                        mdui.mutation();
                    }
                } else {
                    $("#table_data").empty();
                    var $trTemp = $("<tr></tr>");                //往行里面追加 td单元格
                    $trTemp.append("<td>无</td>");
                    $trTemp.append("<td>无</td>");
                    $trTemp.append("<td>无</td>");
                    $trTemp.append("<td>无</td>");
                    $trTemp.append("<td></td>");
                    $trTemp.appendTo("#table_data");
                    mdui.mutation();
                }
            }
        )
    });
});
