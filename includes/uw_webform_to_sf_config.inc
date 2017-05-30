<?php
function uw_webform_to_sf_config_form($form, &$form_state, $webform_node) {
	

  $form['#node'] = $webform_node;
  $form['#tree'] = false;

  $form['nid'] = array(
    '#type' => 'value',
    '#value' => $webform_node->nid,
  );

  //check for an existing record there can only be one per form 
  $config = db_select('webform_to_sf_config')
    ->fields('webform_to_sf_config', array('target','sobject','enabled'))
    ->condition('nid', $webform_node->nid)
    ->execute()->fetchAssoc();


  $form['enabled'] = array(
    '#type' => 'checkbox',
    '#title' => 'Enabled',
    '#default_value' => $config['enabled'],
  );

  $form['target'] = array(
    '#type' => 'textfield',
    '#title' => t('Target'),
    '#description' => t('The REST service to post to'),
    '#size' => 100,
    '#maxlength' => 255,
    '#required' => TRUE,
    '#default_value' => $config['target'],
  );

  $form['sobject'] = array(
    '#type' => 'textfield',
    '#title' => t('SObject'),
    '#description' => t('The sobject to write to'),
    '#size' => 50,
    '#maxlength' => 50,
    '#required' => TRUE,
    '#default_value' => $config['sobject'],
  );

  $form['add_button'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 45,
  );

  return $form;

}


function uw_webform_to_sf_config_form_submit($form, &$form_state) {

  $target = array();
  $target['nid']  = trim($form_state['values']['nid']);
  $target['target']  = trim($form_state['values']['target']);
  $target['sobject'] = trim($form_state['values']['sobject']);
  $target['enabled'] = trim($form_state['values']['enabled']);
  
  $config = db_select('webform_to_sf_config')
    ->fields('webform_to_sf_config', array('target','sobject','enabled'))
    ->condition('nid', $target['nid'])
    ->execute()->fetchAssoc();

  $success = FALSE;

  if($config) {
    $success = drupal_write_record('webform_to_sf_config', $target, 'nid');
  } else {
    $success = drupal_write_record('webform_to_sf_config', $target);
  }

  // Write a log if we weren't able to save the target successfully.
  if ($success === FALSE) {
    watchdog('webform_to_sf', 'There was an error writing sf to salesforce config.', array(), WATCHDOG_ERROR);
  }

  $form_state['redirect'] = 'node/' . $form['#node']->nid . '/webform/sfconfig';

}






