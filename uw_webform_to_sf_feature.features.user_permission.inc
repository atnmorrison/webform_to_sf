<?php
/**
 * @file
 * uw_webform_to_sf_feature.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function uw_webform_to_sf_feature_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'admin webform to sf'.
  $permissions['admin webform to sf'] = array(
    'name' => 'admin webform to sf',
    'roles' => array(
      'administrator' => 'administrator',
      'form editor' => 'form editor',
    ),
    'module' => 'uw_webform_to_sf',
  );

  return $permissions;
}
