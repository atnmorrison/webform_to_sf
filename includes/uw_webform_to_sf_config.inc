<?php
/**
 * @file 
 *
 * The configuration form for setting the parameters for webform to sf
 *
 */

function uw_webform_to_sf_config_form($form, &$form_state, $webform_node) {

  $form['#node'] = $webform_node;
  $form['#tree'] = FALSE;
  $form['nid'] = array(
    '#type' => 'value',
    '#value' => $webform_node->nid,
  );

  //check for an existing record there can only be one per form 
  $config = db_select('webform_to_sf_config')
    ->fields('webform_to_sf_config', array('target', 'sobject', 'enabled'))
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
    '#description' => t('The SObject to write to'),
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
    ->fields('webform_to_sf_config', array('target', 'sobject', 'enabled'))
    ->condition('nid', $target['nid'])
    ->execute()->fetchAssoc();

  $success = FALSE;

  if ($config) {
    $success = drupal_write_record('webform_to_sf_config', $target, 'nid');
  } 
  else {
    $success = drupal_write_record('webform_to_sf_config', $target);
  }

  // Write a log if we weren't able to save the target successfully.
  if ($success === FALSE) {
    watchdog('uw_webform_to_sf', 'There was an error writing Webform to Salesforce config.', array(), WATCHDOG_ERROR);
  }

  $form_state['redirect'] = 'node/' . $form['#node']->nid . '/webform/sfconfig';

}

function uw_webform_to_sf_config_form_validate($form, &$form_state) {
  if (isset($form_state['values']['target']) && !valid_url($form_state['values']['target'], TRUE)) {
    form_set_error('target', t('A valid URL must be entered as a target'));
  }

  if (!preg_match('/^[a-z_0-9]+$/i', $form_state['values']['sobject'])) {
    form_set_error('sobject', t('Only alpha numeric characters and _ can be used in SObject names'));
  }

}









