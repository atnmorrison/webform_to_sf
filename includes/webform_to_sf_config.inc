<?php
function webform_to_sf_config_form($form, &$form_state, $webform_node) {
	

  $form['#node'] = $webform_node;
  $form['#tree'] = false;

  $form['nid'] = array(
    '#type' => 'value',
    '#value' => $webform_node->nid,
  );

  //check for an existing record there can only be one per form 
  $config = db_select('webform_to_sf_config')
    ->fields('target,sobject,enabled')
    ->condition('nid', $webform_node->nid)
    ->execute()->fetchAssoc();


  $form['enabled'] = array(
    '#type' => 'checkbox',
    '#default_value' => $config['enabled'],
  );

  $form['target'] = array(
  	'#type' => 'textfield',
    '#title' => t('Target'),
    '#description' => t('The REST service to post to'),
    '#size' => 20,
    '#maxlength' => 60,
    '#required' => FALSE,
    '#value' => $config['target'],
  );

  $form['sobject'] = array(
  	'#type' => 'textfield',
    '#title' => t('SObject'),
    '#description' => t('The sobject to write to'),
    '#size' => 20,
    '#maxlength' => 60,
    '#required' => FALSE,
    '#value' => $config['sobject'],
  );

  $form['add_button'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 45,
  );

  return $form;

}