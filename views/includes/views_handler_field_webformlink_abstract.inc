<?php
/*
 * @author Klaas Eikelboom  <klaas.eikelboom@civicoop.org>
 * @date 14-Aug-2020
 * @license  AGPL-3.0
 */

abstract class views_handler_field_webformlink_abstract extends views_handler_field {

  /**
   * Constructor to provide additional field to add.
   */
  public function construct() {
    parent::construct();
    $this->additional_fields['id'] = 'id';
  }

  abstract protected function entity();

  protected function findsid($id) {
    $sid = db_query('select s.sid from {webform_submissions} s
                     join {webform_civicrm_links} l on l.sid=s.sid
                     where s.nid = :nid
                     and   l.entity_table = :entity_table
                     and   l.sequence = :sequence
                     and entity_id = :entity_id order by s.sid desc limit 1',[
                       ':nid' => $this->options['nid'],
                       ':entity_table' => $this->entity(),
                       ':sequence' => $this->options['sequence'],
                       ':entity_id' => $id,
    ])->fetchField();
    return $sid;
  }

  /**
   * {@inheritdoc}
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['nid'] = [
      'default' => '',
    ];
    $options['sequence'] = [
      'default' => 1,
    ];
    return $options;
  }

  public function options_form(&$form, &$form_state) {
    $form['webformlink'] =
      [
        '#type' => 'fieldset',
        '#title' => 'Webform Link',
        '#collapsible' => true,
        '#collapsed' => true,
        'nid' => [
          '#type' => 'select',
          '#title' => 'Webform',
          '#options' => webform_civicrm_link_helper::instance()->webforms(),
          '#default_value' => $this->options['nid'],
        ],
        'sequence' => [
          '#type' => 'textfield',
          '#title' => 'Sequence',
          '#default_value' => $this->options['sequence'],
          '#size' => 4,
          '#element_validate' => ['element_validate_number'],
        ],
      ];
    parent::options_form($form, $form_state);
  }

  public function options_submit(&$form, &$form_state) {
    $options = &$form_state['values']['options'];
    if(isset($options['webformlink'])){
      $options['nid'] = $options['webformlink']['nid'];
      $options['sequence'] = $options['webformlink']['sequence'];
    }
    parent::options_submit($form, $form_state);
  }

  public function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  public function render($values) {
    $field = $this->aliases['id'];
    $sid=$this->findsid($values->$field);
    if ($sid) {
      return l('Goto',"node/{$this->options['nid']}/submission/{$sid}");
    } else {
      return false;
    }

  }
}
