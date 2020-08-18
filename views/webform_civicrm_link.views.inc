<?php

function webform_civicrm_link_views_data(){
  $data = [];
  $data['civicrm_contact']['webform_link'] = array(
    'title' => t('Contact Webform'),
    'help' => t('Link to a contact webform'),
    'field' => array(
      'handler' => 'views_handler_field_webformlink_contact',
      'click sortable' => false,
    ),
    $data['civicrm_case']['webform_link'] = array(
      'title' => t('Case Webform'),
      'help' => t('Link to a case webform'),
      'field' => array(
        'handler' => 'views_handler_field_webformlink_case',
        'click sortable' => false,
      ),
    ),
    $data['civicrm_activity']['webform_link'] = array(
      'title' => t('Activity Webform'),
      'help' => t('Link to a activity webform'),
      'field' => array(
        'handler' => 'views_handler_field_webformlink_activity',
        'click sortable' => false,
      ),
    )
  );
  return $data;

}
