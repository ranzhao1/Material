import QtQuick 1.0
import QtWebKit 1.0


WebView {
    signal loadFinished(url address)
    signal loadStarted(url address)

    focus: true

    onLoadFinished: main.loadFinished(url)
    onUrlChanged:  {
        loadStarted(url)
        if (url.toString().indexOf("http://www.facebook.com/connect/login_success.html") == 0) {
            //url = "http://www.renren.com"
        }
    }
    url: "https://www.facebook.com/dialog/oauth?client_id=450289111679614&redirect_uri=http://www.facebook.com/connect/login_success.html&response_type=token&scope=publish_stream,read_stream"


}
