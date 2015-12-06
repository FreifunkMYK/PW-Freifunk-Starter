<?php
$config->scripts->add($config->urls->core . 'wire/modules/Inputfield/InputfieldDatetime/InputfieldDatetime.js');

$page_id = (int) $input->post->select_product; // page ID
$p = $pages->get(1031);
$template = $p->template->name; // this is the template where we will get the fields from


// make a form
$form = $modules->get('InputfieldForm');
$form->method = 'post';
$form->action = './';
$form->attr("id+name",'subscribe-form');


// add the page's fields to the form
$fields = $p->fieldgroup;
foreach($fields as $field) {
    $inputfield = $fields->{$field->name}->getInputfield($p);
    $form->append($inputfield);
}


// add template name field to the form
$field = $modules->get("InputfieldHidden");
$field->attr('id', 'Inputfield_template_name');
$field->attr('name', 'template_name');
$field->value = $template;
$form->append($field); // append the field


// add a submit button to the form
$submit = $modules->get('InputfieldSubmit');
$submit->name = 'save_new_aanvraag';
$submit->attr("value", "Go");
$form->append($submit);


// process the form if it was submitted
if($this->input->post->save_new_aanvraag) {
    // now we assume the form has been submitted.
    // tell the form to process input from the post vars.
    $form->processInput($this->input->post);


    // see if any errors occurred
    if( count( $form->getErrors() )) {
      $form->setMarkup(array(
                  'list' => "<div {attrs}>{out}</div>",
                  'item' => "<div {attrs}>{out}</div>"
              ));
        // re-render the form, it will include the error messages
        $content = $form->render();
    } else {
        // successful form submission
        $np = new Page(); // create new page object
        $np->template = $form->get("template_name")->value; // set template
        $np->parent = $pages->get('/aanvraag/'); // set the parent
        $np->of(false); // turn off output formatting before setting values
        $np->save();


        foreach($np->fields as $f) {
            $np->set($f->name, $form->get($f->name)->value);
        }
        $np->save(); //create the page


        $content = "<p>Page saved.</p>";
    }
} else {
    $form->setMarkup(array(
                'list' => "<div {attrs}>{out}</div>",
                'item' => "<div {attrs}>{out}</div>"
            ));
    $content = $form->render();
}
