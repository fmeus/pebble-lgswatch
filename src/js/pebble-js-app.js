var initialized = false;


Pebble.addEventListener( "ready", function(e) {
	initialized = true;
});


Pebble.addEventListener( "appmessage", function(e) {
	localStorage.setItem( "status", e.payload.status );
	localStorage.setItem( "language", e.payload.language );
	localStorage.setItem( "format", e.payload.format );
});


Pebble.addEventListener( "showConfiguration", function(e) {
	Pebble.openURL( "http://fmeus.github.io/www/pebble_lgs/lgs_watch.html?status=" + localStorage.getItem( "status" ) + "&language=" + localStorage.getItem( "language" ) + "&format=" + localStorage.getItem( "format" ) );
});


Pebble.addEventListener( "webviewclosed", function(e) {
 // console.log("Configuration window returned: " + e.response);
 
	if ( ( typeof( e.response ) == 'string') && ( e.response.length > 0 ) ) {
		try {
			var options = JSON.parse( e.response );
			localStorage.setItem( "status", options.status );
			localStorage.setItem( "language", options.language );
			localStorage.setItem( "format", options.format );
			Pebble.sendAppMessage( options );
		} catch(e) {
		}
	}
});