
<?php

/**
 * @file
 * Manages validation rules administration UI.
 */

/**
 * Menu callback function to show an overview of the existing validation rules, and the option to add a rule.
 */
function webform_civicrm_link_manage($node) {

  $output = [];
  $output['webform_civicrm_link_manage_form'] = drupal_get_form('_webform_civicrm_link_manage_form',$node);
  return $output;
}

function _webform_civicrm_link_manage_form($form, &$form_state, $node){
  $form = [];
  $nid = $node->nid;
  $enabled = db_query('select enabled from {webform_civicrm_links_config} where nid = :nid',[
    ':nid' => $nid
  ])->fetchField();
  $form['enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable CiviCRM Webform link'),
    '#description' => t('If enabled, all CiviCRM Submission are stored in a seperate table'),
    '#default_value' => $enabled,
  );
  $form['nid'] = [
    '#type' => 'hidden',
    '#value' => $nid,
  ];
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Enable or Disable'),
  );
  return $form;
}

function _webform_civicrm_link_manage_form_submit($form, &$form_state) {
  db_merge('webform_civicrm_links_config')
    ->key(['nid' => $form_state['values']['nid']])
    ->fields(['enabled' =>  $form_state['values']['enabled']])
    ->execute();
  drupal_set_message(t('The order of the validation rules has been saved.').$form_state['values']['nid']);
}



