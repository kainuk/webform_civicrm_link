<?php

function webform_civicrm_link_views_data(){
  $data = [];
  $data['civicrm_contact']['webform_link'] = array(
    'title' => t('Contact Webform'),
    'help' => t('Link to a contact webform'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  return $data;

}
