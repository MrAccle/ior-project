var serverBaseUrl = "http://172.16.100.3:8080/"

window.AjaxJsonData = function (type, urlParam, successFunc, data) {
    if (data != null) {
        $.ajax({
            type: type,
            url: serverBaseUrl + urlParam,
            dataType: 'json',
            headers: {
                "Content-Type": "application/json;charset=UTF-8"
            },
            async: true,
            data: JSON.stringify(data),
            success: successFunc,
            error: function (e) {
                console.log(e)
                layer.closeAll('loading');
                alert('数据初始化错误，请联系管理员排查')
            }
        });
    } else {
        $.ajax({
            type: type,
            url: serverBaseUrl + urlParam,
            dataType: 'json',
            headers: {
                "Content-Type": "application/json;charset=UTF-8"
            },
            async: true,
            // data: JSON.stringify(data),
            success: successFunc,
            error: function (e) {
                console.log(e)
                layer.closeAll('loading');
                alert('数据初始化错误，请联系管理员排查')
            }
        });
    }

}