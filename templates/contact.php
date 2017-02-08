<?php
$script = "<script>
		$('#myForm')
		.on('Valid', function (){
			var name = $('input#name').val();
			var email = $('input#email').val();
			var message = $('input#message').val();
			
			//Data for Massage
			var dataString = 'name=' + name + 
					'&email=' + email +
					'&message=' + message;

			$.ajax({
				type: \"POST\",
				url: \"scripts/mail.php\",
				data: dataString,
				success: function() {
					$('contactform').html(\"<div id='thenks'></div>\");
						$('#thanks').html(\"<h2>Danke</h2>\")
						.append(\"<p>\" + name + \" wir versuchen dir so schnell wie möglich zu Antworten.</p>\")
						.hide()
						.fadein(1500);
				},

			}); //ajax call
			
			return false;	
		})
</script>";
$content=renderPage();
